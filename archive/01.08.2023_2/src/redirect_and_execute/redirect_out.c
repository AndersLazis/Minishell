/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:10 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 20:24:29 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_in_from(char *filename, t_data *data)
{
	int	input;

	input = 0;
	input = open(filename, O_RDONLY, 0644);
	if (input == ERROR)
	{
		data->exit_code = 1;
		perror(filename);
		data->error_open_file = true;
		return ;
	}
	dup2(input, STDIN_FILENO);
	close(input);
}

static void	redirect_output_to(t_data *data, int truncorappend)
{
	int	output;

	output = 0;
	if (truncorappend == TRUNCATE)
		output = open(data->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		output = open(data->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output == ERROR)
	{
		data->exit_code = 1;
		perror(data->filename);
		data->error_open_file = true;
		return ;
	}
	dup2(output, STDOUT_FILENO);
	close(output);
}

static bool	next_redirect(t_data *data)
{
	while (data->command_array[data->index][data->m] != NULL)
	{
		if ((ft_strcmp(data->command_array[data->index][data->m], ">") == 0 \
		|| ft_strcmp(data->command_array[data->index][data->m], ">>") == 0 \
		||ft_strcmp(data->command_array[data->index][data->m], "<") == 0))
		{
			data->m += 1;
			return (true);
		}
		data->m += 1;
	}
	return (false);
}

bool	redirect_out(t_data *data)
{
	char	**args;
	int		i;

	data->m = 0;
	while (next_redirect(data) == true && data->error_open_file == false)
	{
		args = split_args(data->command_array[data->index][data->m], data);
		data->filename = NULL;
		data->filename = strdup(args[0]);
		i = 0;
		while (args[i] != NULL)
			free(args[i++]);
		free(args);
		if (ft_strcmp(data->command_array[data->index][data->m - 1], ">>") == 0)
			redirect_output_to(data, APPEND);
		else if (ft_strcmp(data->command_array[data->index][data->m - 1], ">") == 0)
			redirect_output_to(data, TRUNCATE);
		else if (ft_strcmp(data->command_array[data->index][data->m - 1], "<") == 0 && data->heredoc_flag == 0)
			redirect_in_from(data->filename, data);
		if (data->exit_code == true)
			break ;
		free(data->filename);
	}
	return (true);
}
