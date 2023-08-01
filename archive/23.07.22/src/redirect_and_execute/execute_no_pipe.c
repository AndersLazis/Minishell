/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/28 20:51:27 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_no_pipe(t_data *data)
{
	char	*path;
	pid_t	pid;

	data->command = data->command_array[0][0]; // Add case if the redirection is at the beginning
	data->split = ft_split_arguments(data->command, data);
	data->index = 0;
	redirect_in(data);
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
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed");
			exit (0);
		}
		if (pid == 0)
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
	wait(NULL);
	close(0);
	close(1);
	dup2(data->save_in, 0);
	dup2(data->save_out, 1);
}