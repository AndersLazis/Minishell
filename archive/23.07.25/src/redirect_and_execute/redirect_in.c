/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:18 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 01:14:31 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_in_from(char *filename)
{
	static int	input;

	if (input != 0)
		close(input);
	input = open(filename, O_RDONLY, 0644);
	if (input == ERROR)
	{
		printf("Error open file \n");
		exit (0);
	}
	dup2(input, STDIN_FILENO);
	close(input);
}

static bool	next_redirect_in(t_data *data)
{
	while (data->command_array[data->index][data->m] != NULL)
	{
		if (ft_strcmp(data->command_array[data->index][data->m], "<") == 0)
		{
			data->m += 1;
			if (ft_strcmp(data->command_array[data->index][data->m], ">") == 0)
			{
				data->command_array[data->index][data->m][0] = '<';
				data->m += 1;
			}
			return (true);
		}
		data->m += 1;
	}
	return (false);
}

bool	redirect_in(t_data *data)
{
	char	*filename;

	data->m = 0;
	while (next_redirect_in(data) == true)
	{
		filename = data->command_array[data->index][data->m];
		filename = trimwhitespace(filename);
		if (filename == NULL)
		{
			printf("No file\n");
			exit (0);
		}
		redirect_in_from(filename);
	}
	return (true);
}
