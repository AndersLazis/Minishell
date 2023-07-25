/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 12:12:44 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	waitpid_exitstatus(t_data *data)
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

void	shell_loop(t_data *data)
{
	char	*command_line;
	int		status;
	
	setup_signal_handling();
	while (1)
	{
		command_line = readline("♖♘♗♕♔♗♘♖>> ");
		command_line = handle_heredoc(command_line, data);
		printf("command_line:%s\n", command_line);
		add_history(command_line);
		if (command_line != NULL)
		{
			lexer(command_line, data);
			syntax_checker(data);
		}
		else
			exit (0);
		if (data->error != -1)
		{
			data->i = 0;
			printf("Lexer-Start \n");
			while (data->lexer_output[data->i] != NULL)
				printf("\t %s \n", data->lexer_output[(data->i)++]);
			printf("Lexer-End \n");

			redirect_and_execute(data);
			waitpid_exitstatus(data);
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
	increment_shell_level(data);
	update_envp(data);
	shell_loop(data);
	return (EXIT_SUCCESS);
}
