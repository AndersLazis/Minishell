/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 20:51:10 by aputiev          ###   ########.fr       */
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

static void	reset_function(t_data *data)
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
	while (1)
	{
		command_line = readline("♖♘♗♕♔♗♘♖>> ");
		if(heredoc_exist(command_line, data))	//<-changed_19.07.2023
			command_line = handle_heredoc(command_line, data);	//<-changed_19.07.2023
		add_history(command_line);
		if (command_line != NULL)
		{
			lexer(command_line, data);
			syntax_checker(data);
			if (data->error != -1)
				split_into_commands(data);
		}
		else
			ft_exit(data);
		if (data->error != -1 && data->lexer_output[0] != NULL)
		{
			i = 0;
			printf("Lexer-Start \n");
			while (data->lexer_output[i] != NULL)
				printf("\t %s \n", data->lexer_output[i++]);
			printf("Lexer-End \n");
		
			redirect_and_execute(data);
		}
		//reset_function(data); // Reset everything for the next input!
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
	data->ac = ac;
	data->av = av;
	data->envp = env;
	init_env_unsorted(data, env);
	init_env_sorted(data, env);
	increment_shell_level(data);
	update_envp(data);
	int i = 0;
	while(data->envp[i]!=NULL)
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	minishell_loop(data);
	return (EXIT_SUCCESS);
}
