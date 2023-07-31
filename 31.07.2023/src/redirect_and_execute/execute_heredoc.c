/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:54:16 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 00:21:30 by mschulme         ###   ########.fr       */
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

static bool	next_heredoc(t_data *data)
{
	while (data->command_array[data->index][data->m] != NULL)
	{
		if (ft_strcmp(data->command_array[data->index][data->m], "<<") == 0)
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
		}
		free(line);
		exit (0);
	}
}

void	execute_heredoc(t_data *data)
{
	char	**arguments;
	char	*delimiter;
	int		i;

	data->heredoc_flag = 0;
	data->input = open("tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	data->m = 0;
	while (next_heredoc(data) == true)
	{
		data->heredoc_flag = 1;
		if (data->lexer_output[data->m][0] == '\"')
			data->nb_double_quotes = -1;
		arguments = ft_split_arguments(data->lexer_output[data->m], data);
		delimiter = arguments[0];
		i = 1;
		while (arguments[i] != NULL)
			data->split = add_string(data->split, arguments[i++]);
		fork_heredoc(data, delimiter);
		wait(NULL);
		close(data->input);
		if (g_flags == SIGINT)
			data->error_open_file = true;
		data->m += 1;
	}
}
