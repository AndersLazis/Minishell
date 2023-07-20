/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:20:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/18 12:44:47 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_into_commands(t_data *data)
{
	int	nb;
	int	i;
	int	j;

	i = 0;
	nb = 0;
	while (data->lexer_output[i] != NULL)
	{	printf("lexer_output[%d]:%s\n", i, data->lexer_output[i]);
		if (data->lexer_output[i][0] == '|')
			nb++;
		i++;
	}
	data->pipe_count = nb;
	data->command_array = malloc(1000 * sizeof (char **));
	i = 0;
	while (i < 1000)
	{
		data->command_array[i] = ft_calloc(1000 * sizeof (char *), 1);
		i++;
	}
	i = 0;
	j = 0;
	nb = 0;
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
	data->command_array[nb + 2] = NULL;
}
