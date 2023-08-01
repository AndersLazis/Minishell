/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 23:55:40 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clean_up(t_data *data, bool command)
{
	int	j;

	j = 0;
	close(0);
	close(1);
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
	if (command == true)
	{
		j = 0;
		while (data->split[j] != NULL)
			free(data->split[j++]);
		free(data->split);
	}
}

static void	execute(t_data *data)
{
	int		status;
	pid_t	pid;

	if (execute_build_in(data) == 0)
		;
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("");
			exit (EXIT_FAILURE);
		}
		if (pid == 0)
			execution(data);
		if (waitpid(pid, &status, 0) == -1)
			exit (EXIT_FAILURE);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		close(data->input);
	}
}

static void	arguments_command(t_data *data)
{
	char	**arguments;
	int		i;
	int		j;

	i = 0;
	while (data->lexer_output[i] != NULL)
	{
		if (data->lexer_output[i][0] == '>' || data->lexer_output[i][0] == '<')
		{
			arguments = split_args(data->lexer_output[i + 1], data);
			j = 1;
			while (arguments[j] != NULL)
			{
				data->split = add_string(data->split, arguments[j]);
				j++;
			}
		}
		i++;
	}
}

void	execute_no_pipe(t_data *data)
{
	bool	cmd;

	data->error_open_file = false;
	data->index = 0;
	data->input = 0;
	cmd = true;
	if (data->lexer_output[0][0] == '>' || data->lexer_output[0][0] == '<')
	{
		cmd = false;
		data->split = NULL;
	}
	else
		data->split = split_args(data->lexer_output[0], data);
	arguments_command(data);
	execute_heredoc(data);
	if (data->heredoc_flag == 1)
	{
		data->input = open("tmp/temp.txt", O_RDWR, 0644);
		dup2(data->input, STDIN_FILENO);
	}
	redirect_out(data);
	if ((cmd == true || data->split != NULL) && data->error_open_file == false)
		execute(data);
	clean_up(data, cmd);
}
