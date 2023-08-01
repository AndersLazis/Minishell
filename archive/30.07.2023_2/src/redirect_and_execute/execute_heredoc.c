/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:54:16 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/29 23:40:26 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*dollar_substitution(t_data *data, char *line)
{
	char	*new_str;
	
	data->i = 0;
	data->j = 0;
	new_str = calloc(2500, 1);
	if (new_str == NULL)
		exit (EXIT_FAILURE);
	while (line[data->i] != 0)
	{
		if (line[data->i] == '$')
			dollarsignheredoc(line, data, new_str);
		else
		{
			new_str[data->j] = line[data->i];
			data->j += 1;
			data->i++;
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

void	execute_heredoc(t_data *data)
{
	char	**arguments;
	char	*delimiter;
	char	*line;
	int		pid;
	int		i;
	
	data->m = 0;
	data->input = open("tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (next_heredoc(data) == true)
	{
		data->heredoc_flag = 1;
		arguments = ft_split_arguments(data->lexer_output[data->m], data);
		delimiter = arguments[0];
		i = 1;
		while (arguments[i] != NULL)
			data->split = add_string(data->split, arguments[i++]);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			while ((line = readline("> ")) != NULL)
			{
				if (ft_strcmp(line, delimiter) == 0)
					break;
				line = dollar_substitution(data, line); // Check for double quotes
				write(data->input, line, ft_strlen(line));
				write(data->input, "\n", 1);
			}
			free(line);
			exit (0);
		}
		wait(NULL);
		close(data->input);
		if (g_flags == SIGINT)
			data->error_open_file = true;
		data->m += 1;
	}
}
