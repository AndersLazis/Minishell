/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:20:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 21:33:37 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	helper(t_data *data);

void	split_into_commands(t_data *data)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (data->lexer_output[i] != NULL)
	{
		if (data->lexer_output[i][0] == '|')
			nb++;
		i++;
	}
	data->pipe_count = nb;
	data->cmd_arr = ft_calloc((nb + 1) * sizeof(char **), 1);
	if (data->cmd_arr == NULL)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < nb + 1)
	{
		data->cmd_arr[i] = ft_calloc(200 * sizeof(char *), 1);
		if (data->cmd_arr[i] == NULL)
			exit (EXIT_FAILURE);
		i++;
	}
	helper(data);
}

static void	helper(t_data *data)
{
	int	nb;
	int	i;
	int	j;

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
			data->cmd_arr[nb][j] = data->lexer_output[i];
			j++;
		}
		i++;
	}
}
