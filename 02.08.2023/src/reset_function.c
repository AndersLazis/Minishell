/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:47:36 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 21:33:37 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_function(char *command_line, t_data *data)
{
	int	i;

	i = 0;
	while (data->lexer_output[i] != NULL)
	{
		free(data->lexer_output[i]);
		i++;
	}
	free(data->lexer_output);
	free(command_line);
	if (data->error != -1)
	{
		i = 0;
		while (i < data->pipe_count + 1)
		{
			free(data->cmd_arr[i]);
			i++;
		}
		free(data->cmd_arr);
	}
}
