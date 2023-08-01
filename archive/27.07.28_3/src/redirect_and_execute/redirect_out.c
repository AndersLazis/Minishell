/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:10 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/29 20:59:56 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_output_to(t_data *data, int truncorappend)
{
	static int	output;

	if (output != 0)
		close(output);
	if (truncorappend == TRUNCATE)
		output = open(data->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		output = open(data->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output == ERROR)
	{
		data->exit_code = 1;
		perror(NULL);
		data->error_open_file = true;
		return ;
	}
	dup2(output, STDOUT_FILENO);
	close(output);
}

static bool	next_redirect_out(t_data *data)
{
	while (data->command_array[data->index][data->m] != NULL)
	{
		if ((ft_strcmp(data->command_array[data->index][data->m], ">") == 0 \
		|| ft_strcmp(data->command_array[data->index][data->m], ">>") == 0))
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
	char	**arguments;
	int		i;
	
	data->m = 0;
	while (next_redirect_out(data) == true && data->error_open_file == false)
	{
		data->filename = data->command_array[data->index][data->m];
		arguments = ft_split_arguments(data->filename, data);
		data->filename = arguments[0];
		i = 1;
		while (arguments[i] != NULL)
			data->split = add_string(data->split, arguments[i++]);
		if (ft_strcmp(data->command_array[data->index][data->m - 1], ">>") == 0)
			redirect_output_to(data, APPEND);
		else
			redirect_output_to(data, TRUNCATE);
	}
	return (true);
}
