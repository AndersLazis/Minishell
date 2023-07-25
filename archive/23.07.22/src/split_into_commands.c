/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:20:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 19:08:30 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_into_commands(t_data *data)
{
	int	nb;
	int	i;
	int	j;

	nb = 0;
	i = 0;
	while (data->lexer_output[i] != NULL)
	{
		if (data->lexer_output[i][0] == '|')
			nb++;
		i++;
	}
	data->pipe_count = nb;
	data->command_array = ft_calloc((nb + 1) * sizeof(char **), 1);
	if (data->command_array == NULL)
	{
		printf("Malloc Error");
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < nb + 1)
	{
		data->command_array[i] = ft_calloc(100 * sizeof(char *), 1);
		if (data->command_array[i] == NULL)
		{
			printf("Malloc Error");
			exit (EXIT_FAILURE);
		}
		i++;
	}
	nb = 0;
	i = 0;
	j = 0;
	while (data->lexer_output[i] != NULL)
	{
		if (data->lexer_output[i][0] == '|')
		{
			nb++;
			j = 0;
		}
		else
		{
			data->command_array[nb][j] = data->lexer_output[i];
			j++;
		}
		i++;
	}
}
