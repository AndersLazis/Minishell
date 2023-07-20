/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 21:37:55 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	waitpid_exitstatus(t_data *data)
{
	int	exit_status;
	int	status;
	
	if (waitpid(data->pid, &status, 0) == -1)
	{
		perror("waitpid() failed");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("Exit status was %d\n", exit_status);
	}
}

static void free_lexer(t_data *data)
{
	int	i;

	i = 0;
	while (i < 1000)
	{
		free(data->lexer_output[i]);
		free(data->command_array[i]);
		i ++;
	}
	free(data->lexer_output);
	free(data->command_array);
}

void	minishell_loop(t_data *data)
{
	char	*command_line;
	int		i;
	
	setup_signal_handling();
	data->save_in = dup(STDIN_FILENO);
	data->save_out = dup(STDOUT_FILENO);
	while (1)
	{
		command_line = readline("♖♘♗♕♔♗♘♖>> ");
		add_history(command_line);
		if (command_line != NULL)
		{
			lexer(command_line, data);
			split_into_commands(data);
			syntax_checker(data);
		}
		else
			exit (0);
		if (data->error != -1 && data->lexer_output[0] != NULL)
		{
			i = 0;
			printf("Lexer-Start \n");
			while (data->lexer_output[i] != NULL)
				printf("\t %s \n", data->lexer_output[i++]);
			printf("Lexer-End \n");
		
			redirect_and_execute(data);
		}
		free_lexer(data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (EXIT_FAILURE);
	data->ac = ac;
	data->av = av;
	data->envp = env;
	init_env_unsorted(data, env);
	init_env_sorted(data, env);
	increment_shell_level(data);
	update_envp(data);
	minishell_loop(data);
	return (EXIT_SUCCESS);
}
