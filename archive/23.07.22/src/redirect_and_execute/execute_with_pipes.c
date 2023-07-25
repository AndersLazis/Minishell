/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 16:00:26 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_with_pipes(t_data *data)
{
	int		pipes[1000][2]; // Maximum number of commands
	pid_t	pid;
	char	*path;
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
			data->command = data->command_array[i][0];
			data->split = ft_split_arguments(data->command, data);
			path = find_path(data->split[0], data->envp);
			if (path == NULL)
				execve(data->split[0], data->split, data->envp);
			else
				execve(path, data->split, data->envp);
			printf("minishell: command not found: %s\n", data->split[0]);
			exit (0);
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
	i = 0;
	while (i < data->pipe_count + 1)
	{
		wait(NULL);
		i++;
	}
}

/*
	path = find_path(data->split[0], data->envp);
	if (path == NULL)
		execve(data->split[0], data->split, data->envp);
	else
		execve(path, data->split, data->envp);
	printf("minishell: command not found: %s\n", data->split[0]);
*/

/*
static int	start_program(int in, int out, t_data *data)
{
	char	*path;

	
	data->pid = fork();
	if (data->pid == -1)
	{
		printf("fork error");
		return (-1);
	}
	if (data->pid == 0)
	{
		redirect_in(data);
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		redirect_out(data);
		
		data->command = data->command_array[data->index][0];
		data->split = ft_split_arguments(data->command, data);
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
		exit (0);
	}
	return (data->pid);
}

void	redirect_and_execute(t_data *data)
{
	char	*path;
	int		fd[2];
	int		in;
	int		pid;

	in = 0;
	data->index = 0;
	while (data->pipe_count > 0 && data->index < data->pipe_count)
	{
		if (pipe(fd) == -1)
			printf("fork error");
		start_program(in, fd[1], data);
		close(fd[1]);
		in = fd[0];
		data->index += 1;
	}
	
	if (in != 0)
		dup2(in, 0);
		
	redirect_in(data);
	redirect_out(data);
	data->command = data->command_array[data->index][0];
	data->split = ft_split_arguments(data->command, data);
	if (ft_strcmp(data->split[0], "exit") == 0 && data->pipe_count == 0)
		ft_exit(data);
	else if (ft_strcmp(data->split[0], "cd") == 0 && data->pipe_count == 0)
		ft_cd(data);
	else if (ft_strcmp(data->split[0], "pwd") == 0 && data->pipe_count == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->split[0], "echo") == 0 && data->pipe_count == 0)
		ft_echo(data);
	else if (ft_strcmp(data->split[0], "env") == 0 && data->pipe_count == 0)
		ft_env(data);
	else if (ft_strcmp(data->split[0], "export") == 0 && data->pipe_count == 0)
		ft_export(data);
	else if (ft_strcmp(data->split[0], "unset") == 0 && data->pipe_count == 0)
		ft_unset(data);
	else 
	{
		pid = fork();
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		if (pid == 0)
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
			exit (0);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(data->pid, NULL, 0);
	waitpid(pid, NULL, 0);
	close(0);
	dup2(data->save_in, STDIN_FILENO);
	close(1);
	dup2(data->save_out, STDOUT_FILENO);
}
*/