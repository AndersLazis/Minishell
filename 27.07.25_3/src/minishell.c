/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 21:41:44 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_loop(t_data *data)
{
	char	*command_line;
	int		i;

	setup_signal_handling();
	g_flags = 0;
	while (1)
	{
		//data->exit_code = code;
				//	setup_signal_handling();
		command_line = readline("♖♘♗♕♔♗♘♖>> ");
		add_history(command_line);
		if (command_line != NULL)
		{
			lexer(command_line, data);
			if (data->error != -1)
				syntax_checker(data);
		}
		else
		{
			kill(0, SIGCHLD);
			exit (0);
		}
		if (data->error != -1)
		{
			i = 0;
			printf("Lexer-Start \n");
			while (data->lexer_output[i] != NULL)
				printf("\t %s \n", data->lexer_output[i++]);
			printf("Lexer-End \n");
			split_into_commands(data);
			g_flags = 1;
			if (data->pipe_count == 0)
				execute_no_pipe(data);
			else
				execute_with_pipes(data);
			g_flags = 0;
		}
		reset_function(command_line, data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("");
		return (EXIT_FAILURE);
	}
	data->save_in = dup(STDIN_FILENO);
	data->save_out = dup(STDOUT_FILENO);
	data->exit_code = 0;
	data->envp = env;
	data->ac = ac;
	data->av = av;
	init_env_unsorted(data, env);
	init_env_sorted(data, env);
	increment_shell_level(data);
	data->envp = NULL;
	update_envp(data);
	minishell_loop(data);
	return (EXIT_SUCCESS);
}
