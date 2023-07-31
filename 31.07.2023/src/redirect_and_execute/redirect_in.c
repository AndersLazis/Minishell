/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:18 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/29 22:12:29 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_in_from(char *filename, t_data *data)
{
	static int	input;

	if (input != 0)
		close(input);
	input = open(filename, O_RDONLY, 0644);
	if (input == ERROR)
	{
		data->exit_code = 1;
		perror(filename);
		data->error_open_file = true;
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
	char	**arguments;
	int		i;

	data->m = 0;
	while (next_redirect_in(data) == true)
	{
		filename = data->command_array[data->index][data->m];
		arguments = ft_split_arguments(filename, data);
		filename = arguments[0];
		i = 1;
		while (arguments[i] != NULL)
		{
			data->split = add_string(data->split, arguments[i]);
			i++;
		}
		redirect_in_from(filename, data);
		if (data->error_open_file == true)
			break ;
	}
	return (true);
}
