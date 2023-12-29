/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by aputiev           #+#    #+#             */
/*   Updated: 2023/08/03 20:14:21 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clean_up(t_data *data)
{
	int	j;

	j = 0;
	close(0);
	close(1);
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
	if (data->split != NULL)
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

static void	arguments_command_help(t_data *data)
{
	char	**temp;
	char	**arguments;
	int		i;
	int		j;

	i = 0;
	while (data->lexer_output[i] != NULL)
	{
		if (data->lexer_output[i][0] == '>' || data->lexer_output[i][0] == '<')
		{
			arguments = split_args(data->lexer_output[i + 1], data);
			free(arguments[0]);
			j = 1;
			while (arguments[j] != NULL)
			{
				temp = add_string(data->split, arguments[j]);
				free(data->split);
				data->split = temp;
				free(arguments[j]);
				j++;
			}
			free(arguments);
		}
		i++;
	}
}

void	execute_no_pipe(t_data *data)
{
	data->error_open_file = false;
	data->index = 0;
	data->input = 0;
	data->cmd = true;
	if (data->lexer_output[0][0] == '>' || data->lexer_output[0][0] == '<')
	{
		data->cmd = false;
		data->split = NULL;
	}
	else
		data->split = split_args(data->lexer_output[0], data);
	arguments_command_help(data);
	execute_heredoc(data);
	if (data->heredoc_flag == 1)
	{
		data->input = open("tmp/temp.txt", O_RDWR, 0644);
		dup2(data->input, STDIN_FILENO);
	}
	redirect_out(data);
	if ((data->cmd == true || data->split != NULL)
		&& data->error_open_file == false)
		execute(data);
	clean_up(data);
}
