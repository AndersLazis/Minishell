/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:54:16 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 23:55:40 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	heredoc_pipes(t_data *data)
{
	char	*filename;
	char	**arguments;
	char	*delimiter;

	data->m = 0;
	while (next_heredoc(data) == true && data->error_open_file == false)
	{
		filename = ft_strjoin(ft_strjoin("tmp/temp", ft_itoa(data->index)), ".txt"); // Fix memory leaks!
		data->input = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		data->heredoc_exists[data->index] = 1;
		if (data->command_array[data->index][data->m][0] == '\"')
			data->nb_double_quotes = -1;
		arguments = split_args(data->command_array[data->index][data->m], data);
		delimiter = arguments[0];
		fork_heredoc(data, delimiter);
		wait(NULL);
		close(data->input);
		if (g_flags == SIGINT)
			data->error_open_file = true;
		data->m += 1;
		// free ft_splitarguments
	}
}
