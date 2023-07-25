/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/16 19:25:34 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	redirect_pipe(t_data *data, readwrite pipes[2])
{
	data->pid = fork();
	if (data->pid == CHILD)
	{
		redirect_in(data);
		//connect(pipes);
		redirect_out(data);
		return (true);
	}
	return (false);
}

static void	execute(t_data *data)
{
	bool				child_process;
	static readwrite	pipes[2];
	char				*path;
	int					pid;	
			
	if (pipe((pipes[CURRENT])) == ERROR)
		printf("Error");
	ft_heredoc(data);	//<-------------------------------------------------added 16.07.2023
	// if(data->heredoc_flag == 1)
	// 	redirect(heredoc_args(data));
	child_process = redirect_pipe(data, pipes);
	if (child_process == true && data->pid == 0) // Everything runs in the child process!
	{	printf("data->command:%s\n", data->command);
		if(data->heredoc_flag !=1)
			data->split = ft_split_arguments(data->command, data);
		else if(data->heredoc_flag ==1)
			data->split = ft_split_arguments_with_heredoc(data->command, data);
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
			//printf("minishell: command not found: %s\n", data->split[0]);
		}
		exit (0);
	}
}

void	redirect_and_execute(t_data *data)
{
	data->m = 0;
	while (data->lexer_output[data->m] != NULL)
	{
		data->command = data->lexer_output[data->m];
		(data->m)++;
		execute(data);
	}
}
