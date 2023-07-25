/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/23 19:08:25 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_no_pipe(t_data *data)
{
	bool	command;
	char	*path;
	pid_t	pid;
	int		exit_code;	//<-changed_23.07.23

	command = true;
	if (data->lexer_output[0][0] == '>' || data->lexer_output[0][0] == '<')
		command = false;
	else
	{	
		data->command = data->lexer_output[0];
		data->split = ft_split_arguments(data->command, data);
	}	
	data->index = 0;
	redirect_in(data);
	redirect_out(data);
	if (command == true)
	{
		if (ft_strcmp(data->split[0], "exit") == 0)
			ft_exit(data, 0);	//<-changed_23.07.23
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
		else if (ft_strcmp(data->split[0], "$?") == 0)
			ft_dollar_question_mark(data);
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
				exit (127);	//<-changed_23.07.23
			}
		}
		//wait(NULL);	//<-changed_23.07.23
		wait(&exit_code);	//<-changed_23.07.23
		data->exit_code = exit_code;	//<-changed_23.07.23
	}
	close(0);
	close(1);
	dup2(data->save_in, 0);
	dup2(data->save_out, 1);
	int j = 0;
	while (data->split[j] != NULL)
	{
		free(data->split[j]);
		j++;
	}
	free(data->split);
}
