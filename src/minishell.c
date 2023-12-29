/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by aputiev           #+#    #+#             */
/*   Updated: 2023/08/03 19:51:57 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_signal_loop(t_data *data)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler_quit);
	if ((g_flags == 2 || g_flags == 3) && data->heredoc_flag != 1)
	{
		data->exit_code = 128 + g_flags;
		g_flags = 0;
	}
	data->command_line = readline("♖♘♗♕♔♗♘♖>> ");
	add_history(data->command_line);
	if (g_flags == SIGINT || g_flags == SIGQUIT)
		data->exit_code = 1;
	g_flags = 0;
	signal(SIGINT, signal_int_nothing);
}

void	minishell_loop(t_data *data)
{
	setup_signal_loop(data);
	if (data->command_line != NULL)
	{
		lexer(data->command_line, data);
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
	reset_function(data->command_line, data);
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
	while (1)
		minishell_loop(data);
	return (EXIT_SUCCESS);
}
