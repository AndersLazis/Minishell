/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/08 22:10:22 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(t_data *data)
{
	char	*command_line;
	
	setup_signal_handling();
	while (1)
	{
		command_line = readline("♖♘♗♕♔♗♘♖ >> ");
		add_history(command_line);
		if (command_line != NULL)
		{
			lexer(command_line, data);
			syntax_checker(data);
		}
		if (data->error != -1)
		{
			data->i = 0;
			printf("Lexer-Start \n");
			while (data->lexer_output[data->i] != NULL)
				printf("\t %s \n", data->lexer_output[(data->i)++]);
			printf("Lexer-End \n");
			if (data->lexer_output[1] == NULL && data->lexer_output[0] != NULL)
			{
				data->split = ft_split_arguments(data->lexer_output[0], data);
				if (!ft_strcmp(data->split[0], "exit"))
					ft_exit(data);
				else if (!ft_strcmp(data->split[0], "cd"))
					ft_cd(data);
				else if (!ft_strcmp(data->split[0], "pwd"))
					ft_pwd(data);
				else if (!ft_strcmp(data->split[0], "echo"))
					ft_echo(data);
				else if (!ft_strcmp(data->split[0], "env"))
					ft_env(data);
				else if (!ft_strcmp(data->split[0], "export"))
					ft_export(data);
				else if (!ft_strcmp(data->split[0], "unset"))
					ft_unset(data);
				else
					executor(data);
			}
			else
				; //input with pipes and redirections
			
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof (t_data));
	if (data == NULL)
		return (EXIT_FAILURE);
	data->ac = ac;
	data->av = av;
	data->envp = env;
	init_env_unsorted(data, env);
	init_env_sorted(data, env);
	shell_loop(data);
	return (EXIT_SUCCESS);
}
