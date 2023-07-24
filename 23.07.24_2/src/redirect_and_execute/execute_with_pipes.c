/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/23 21:28:14 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_with_pipes(t_data *data)
{
	int		pipes[1000][2]; // Maximum number of commands
	bool	command;
	char	*path;
	pid_t	pid;
	int		i;
	int		j;

	i = 0;
	while (i < data->pipe_count)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Pipe Failed");
			exit (0);
		}
		i++;
	}
	data->index = 0;
	i = 0;
	while (i < data->pipe_count + 1)
	{
		command = true;
		if (data->command_array[i][0][0] == '>' || data->command_array[i][0][0] == '<')
			command = false;
		else
		{
			data->command = data->command_array[i][0];
			data->split = ft_split_arguments(data->command, data);
		}
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed");
			exit (0);
		}
		else if (pid == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < data->pipe_count)
				dup2(pipes[i][1], STDOUT_FILENO);
			redirect_in(data);
			redirect_out(data);
			j = 0;
			while (j < data->pipe_count)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			if (command == true)
			{
				if (ft_strcmp(data->split[0], "exit") == 0)
					ft_exit(data);
				else if (ft_strcmp(data->split[0], "cd") == 0)
					ft_cd(data);
				else if (ft_strcmp(data->split[0], "pwd") == 0)
					ft_pwd(data);
				else if (ft_strcmp(data->split[0], "echo") == 0)
					ft_echo(data);
				else if (ft_strcmp(data->split[0], "env") == 0)
					ft_env(data);
				else if (ft_strcmp(data->split[0], "export") == 0)
					ft_export(data);
				else if (ft_strcmp(data->split[0], "unset") == 0)
					ft_unset(data);
				else
				{
					path = find_path(data->split[0], data->envp);
					if (path == NULL)
						execve(data->split[0], data->split, data->envp);
					else
						execve(path, data->split, data->envp);
					printf("minishell: command not found: %s\n", data->split[0]);
					exit (0);
				}
			}
			else
				exit (0);
		}
		j = 0;
		while (data->split[j] != NULL)
		{
			free(data->split[j]);
			j++;
		}
		free(data->split);
		data->index += 1;
		i++;
	}
	i = 0;
	while (i < data->pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	
	int	status;
	i = 0;
	while (i < data->pipe_count + 1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			perror("waitpid() failed");
			exit (EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		i++;
	}
}
