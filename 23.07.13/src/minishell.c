/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/13 17:55:20 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(t_data *data)
{
	char	*command_line;

	setup_signal_handling();
	while (1)
	{
		//int i = 0;
		command_line = readline("♖♘♗♕♔♗♘♖ >> ");
		if (command_line == NULL)
		{
			printf("test");
			exit(0);
		}
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
				// while (data->split[i])
				// {
				// 	printf("arg:%s\n", data->split[i]);
				// 	i++;
				// }
				
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
	
	int i = 0;
	init_env_unsorted(data, env);
	init_env_sorted(data, env);
	increment_shell_level(data); // <-------------------------------------------------------added_july_11
	shell_loop(data);
	return (EXIT_SUCCESS);
}
