/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/18 19:17:36 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute(t_data *data)
{
		/*
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
	*/
}

static int	start_program(int in, int out, t_data *data)
{
	char	*path;

	data->command = data->command_array[data->index][0];
	data->split = ft_split_arguments(data->command, data);
	
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

	in = 0;
	data->index = 0;
	while (data->pipe_count > 0 && data->index < data->pipe_count)
	{
		pipe(fd);
		start_program(in, fd[1], data);
		close(fd[1]);
		in = fd[0];
		waitpid(data->pid, NULL , 0);
		data->index += 1;
	}
	
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
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
		data->pid = fork();
		if (data->pid == -1)
		{
			printf("fork error");
			return ;
		}
		if (data->pid == 0)
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
				exit(0);
		}
		waitpid_exitstatus(data);
	}
	close(0);
	dup2(data->save_in, STDIN_FILENO);
	close(1);
	dup2(data->save_out, STDOUT_FILENO);
}
