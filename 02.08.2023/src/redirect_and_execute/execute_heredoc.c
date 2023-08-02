/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:54:16 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/02 16:54:55 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*dollar_substitution(t_data *data, char *line)
{
	char	*new_str;

	new_str = calloc(2500, 1);
	if (new_str == NULL)
		exit (EXIT_FAILURE);
	data->i = 0;
	data->j = 0;
	while (line[data->i] != 0)
	{
		if (line[data->i] == '$')
			dollarsignheredoc(line, data, new_str);
		else
		{
			new_str[data->j] = line[data->i];
			data->j += 1;
			data->i += 1;
		}
	}
	free(line);
	return (new_str);
}

bool	next_heredoc(t_data *data)
{
	while (data->cmd_arr[data->index][data->m] != NULL)
	{
		if (ft_strcmp(data->cmd_arr[data->index][data->m], "<<") == 0)
		{
			data->m += 1;
			return (true);
		}
		data->m += 1;
	}
	return (false);
}

static void	fork_heredoc(t_data *data, char*delimiter)
{
	char	*line;
	int		pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				break ;
			if (ft_strcmp(line, delimiter) == 0)
				break ;
			if (data->nb_double_quotes != -1)
				line = dollar_substitution(data, line);
			write(data->input, line, ft_strlen(line));
			write(data->input, "\n", 1);
			free(line);
		}
		free(line);
		exit (0);
	}
}

void	execute_heredoc(t_data *data)
{
	char	*delimiter;
	char	**args;
	int		i;

	data->heredoc_flag = 0;
	data->m = 0;
	while (next_heredoc(data) == true && data->error_open_file == false)
	{
		data->input = open("tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		data->heredoc_flag = 1;
		if (data->lexer_output[data->m][0] == '\"')
			data->nb_double_quotes = -1;
		args = split_args(data->lexer_output[data->m], data);
		delimiter = args[0];
		fork_heredoc(data, delimiter);
		wait(NULL);
		i = 0;
		while (args[i] != NULL)
			free(args[i++]);
		free(args);
		close(data->input);
		if (g_flags == SIGINT)
			data->error_open_file = true;
		data->m += 1;
	}
}
