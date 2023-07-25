/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:18 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/13 18:46:06 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_in_from(char *filename)
{
	static int	input_to_file;
	
	if (input_to_file)
		close(input_to_file);
	input_to_file = open(filename, O_RDONLY, 0777);
	if (input_to_file == ERROR)
	{
		printf("Error open file\n");
		exit (0);
	}
	dup2(input_to_file, STDIN_FILENO);
	close(input_to_file);
}

static bool	next_redirect_in(t_data *data)
{
	if (ft_strcmp(data->lexer_output[data->m], "<") == 0 && data->lexer_output[data->m] != NULL)
	{
		data->m += 1;
		return (true);
	}
	return (false);
}

bool	redirect_in(t_data *data)
{
	char	*filename;

	while (next_redirect_in(data) == true)
	{
		filename = data->lexer_output[data->m];
		filename = trimwhitespace(filename);
		data->m += 1;
		if (filename == NULL)
		{
			printf("No file");
			exit (0);
		}
		redirect_in_from(filename);
	}
	return (true);
}
