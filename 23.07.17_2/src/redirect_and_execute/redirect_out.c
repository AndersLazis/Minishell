/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:10 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/13 18:52:44 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_output_to(char *filename, int truncorappend)
{
	static int	output;
	if (output)
		close(output);
	if (truncorappend == TRUNCATE)
		output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (truncorappend == APPEND)
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
	if ((ft_strcmp(data->lexer_output[data->m], ">") == 0 || ft_strcmp(data->lexer_output[data->m], ">>") == 0) && data->lexer_output[data->m] != NULL)
	{
		data->m += 1;
		return (true);
	}
	return (false);
}

bool	redirect_out(t_data *data)
{
	char	*filename;
	
	while (next_redirect_out(data) == true)
	{
		filename = data->lexer_output[data->m];
		filename = trimwhitespace(filename);
		data->m += 1;
		if (ft_strcmp(data->lexer_output[data->m - 2], ">") == 0)
			redirect_output_to(filename, TRUNCATE);
		else if (ft_strcmp(data->lexer_output[data->m - 2], ">>") == 0)
			redirect_output_to(filename, APPEND);
	}
	return (true);
}
