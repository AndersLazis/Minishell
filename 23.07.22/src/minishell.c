/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/22 18:47:18 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_function(char *command_line, t_data *data)
{
	int	i;

	if (data->error != -1 && data->lexer_output[0][0] != 0)
	{
		i = 0;
		while (data->split[i] != NULL)
		{
			free(data->split[i]);
			i++;
		}
		free(data->split);
	}
	i = 0;
	while (i < 1000)
	{
		free(data->lexer_output[i]);
		i++;
	}
	i = 0;
	while (i < data->pipe_count + 1)
	{
		free(data->command_array[i]);
		i++;
	}	
	free(data->lexer_output);
	free(data->command_array);
	free(command_line);
}

void	minishell_loop(t_data *data)
{
	char	*command_line;
	int		i;
	
	setup_signal_handling();
	while (1)
	{
		command_line = readline("♖♘♗♕♔♗♘♖>> ");
		data->heredoc_flag = 0;
		if (heredoc_exist(command_line, data))	//<-changed_19.07.2023
			command_line = handle_heredoc(command_line, data);	//<-changed_19.07.2023
		add_history(command_line);
		if (command_line != NULL)
		{
			lexer(command_line, data);
			syntax_checker(data);
			split_into_commands(data);
		}
		else
			ft_exit(data);
		if (data->error != -1 && data->lexer_output[0][0] != 0)
		{
			i = 0;
			printf("Lexer-Start \n");
			while ( data->lexer_output[i] != NULL)
				printf("\t %s \n", data->lexer_output[i++]);
			printf("Lexer-End \n");
			if (data->pipe_count == 0)
				execute_no_pipe(data);
			else
				execute_with_pipes(data);
		}
		//reset_function(command_line, data);
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
	data->envp = env;
	data->ac = ac;
	data->av = av;
	init_env_unsorted(data, env);
	init_env_sorted(data, env);
	increment_shell_level(data);
	update_envp(data);
	minishell_loop(data);
	return (EXIT_SUCCESS);
}
