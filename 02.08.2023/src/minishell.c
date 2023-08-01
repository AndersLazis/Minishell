/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 23:18:52 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_loop(t_data *data)
{
	char	*command_line;

	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler_quit);
		command_line = readline("♖♘♗♕♔♗♘♖>> ");
		add_history(command_line);
		signal(SIGINT, signal_int_nothing);
		g_flags = 0;
		if (command_line != NULL)
		{
			lexer(command_line, data);
			if (data->error != -1)
				syntax_checker(data);
		}
		else
			exit_ctrl_d(data);
		if (data->error != -1)
		{
			split_into_commands(data);
			if (data->pipe_count == 0)
				execute_no_pipe(data);
			else
				execute_with_pipes(data);
		}
		reset_function(command_line, data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (EXIT_FAILURE);
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
