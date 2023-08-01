/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/30 01:12:49 by mschulme         ###   ########.fr       */
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
	i = 0;
	while (i < data->pipe_count + 1)
	{
		command = true;
		if (data->command_array[i][0][0] == '>' || data->command_array[i][0][0] == '<')
			command = false;
		else
			data->split = ft_split_arguments(data->command_array[i][0], data);
		pid_array[i] = fork();
		if (pid_array[i] < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		else if (pid_array[i] == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < data->pipe_count)
				dup2(pipes[i][1], STDOUT_FILENO);
			/*
			if (data->heredoc_flag == 1 && data->error_open_file == false)
			{
				data->input = open("tmp/temp.txt", O_RDWR, 0644);
				dup2(data->input, STDIN_FILENO);
			}
			*/
			redirect_in(data);
			//if (data->error_open_file == false)
			redirect_out(data);
			j = 0;
			while (j < data->pipe_count)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
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
						if (ft_strncmp(data->split[0], "./", 2) == 0)
						{
							access(data->split[0], X_OK);
							if (errno == EACCES)
								perror(data->split[0]);
							else
								execve(data->split[0], data->split, data->envp);
						}
						else
							perror(data->split[0]);
					}
					else
					{
						execve(path, data->split, data->envp);
						perror(data->split[0]);
					}
					exit (127);
				}
			}
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
