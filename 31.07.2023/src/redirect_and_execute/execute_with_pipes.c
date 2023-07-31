/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 01:42:39 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_with_pipes(t_data *data)
{
	int		pipes[1000][2];
	pid_t	pid_array[1000];
	bool	command;
	char	*path;
	int		i;
	int		j;

	// Read in all of the heredocs

	//////
	i = 0;
	while (i < data->pipe_count)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("");
			exit (EXIT_FAILURE);
		}
		i++;
	}
	data->error_open_file = false;
	data->heredoc_flag = 0;
	data->index = 0;
	data->input = 0;
	/////
	
	i = 0;
	while (i < data->pipe_count + 1)
	{
		command = true;
		if (data->command_array[i][0][0] == '>' || data->command_array[i][0][0] == '<')
		{
			command = false;
			data->split = NULL;
		}
		else
			data->split = ft_split_arguments(data->command_array[i][0], data);
		pid_array[i] = fork();
		if (pid_array[i] < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		if (pid_array[i] == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < data->pipe_count)
				dup2(pipes[i][1], STDOUT_FILENO);
			j = 0;
			while (j < data->pipe_count)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			redirect_in(data);
			if (data->error_open_file == false)
				redirect_out(data);
			if (command == true && data->error_open_file == false)
			{
				if (ft_strcmp(data->split[0], "exit") == 0)
					ft_exit(data);
				else if (ft_strcmp(data->split[0], "cd") == 0)
					ft_cd(data);
				else if (ft_strcmp(data->split[0], "pwd") == 0)
					ft_pwd();
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
					{
						if (searchlist(data->env_sorted, "PATH") == NULL)
							ft_printf(2, "%s: No such file or directory\n", data->split[0]);
						else if (access(data->split[0], F_OK) == -1)
							ft_printf(2, "%s: command not found\n", data->split[0]);
						else if (access(data->split[0], X_OK) == -1)
							perror("");
						else
							execve(data->split[0], data->split, data->envp);
					}
					else
						execve(path, data->split, data->envp);
					exit (127);
				}
			}
			exit (0);
		}
		j = 0;
		if (command == true)
		{
			while (data->split[j] != NULL)
			{
				free(data->split[j]);
				j++;
			}
			free(data->split);
		}
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
	while (i < data->pipe_count)
	{
		if (waitpid(pid_array[i], NULL, 0) == -1)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		i++;
	}
	waitpid(pid_array[data->pipe_count], &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
}
