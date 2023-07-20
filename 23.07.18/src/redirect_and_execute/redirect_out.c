/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:10 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 20:56:57 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_output_to(char *filename, int truncorappend)
{
	static int	output;
	
	if (output != 0)
		close(output);
	if (truncorappend == TRUNCATE)
		output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		output = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (output == ERROR)
	{
		printf("error");
		exit (-1);
	}
	dup2(output, STDOUT_FILENO);
	close(output);
}

static bool	next_redirect_out(t_data *data)
{
	while (data->command_array[data->index][data->m] != NULL)
	{
		if ((ft_strcmp(data->command_array[data->index][data->m], ">") == 0 || ft_strcmp(data->command_array[data->index][data->m], ">>") == 0))
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
	char	*filename;
	
	data->m = 0;
	while (next_redirect_out(data) == true)
	{
		filename = data->command_array[data->index][data->m];
		if (filename == NULL)
			break ;
		filename = trimwhitespace(filename);
		if (ft_strcmp(data->command_array[data->index][data->m - 1], ">>") == 0)
			redirect_output_to(filename, APPEND);
		else
			redirect_output_to(filename, TRUNCATE);
	}
	return (true);
}
