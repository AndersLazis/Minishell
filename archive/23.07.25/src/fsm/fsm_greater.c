/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_greater.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 16:49:47 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_greater(char *str, t_data *data)
{
	data->lexer_output[data->k][data->j] = str[data->i];
	data->j += 1;
	data->i += 1;
	if (space(str[data->i]) == 1)
	{
		data->k += 1;
		data->j = 0;
	}
	else if (character(str[data->i]) == 1)
	{
		data->k += 1;
		data->j = 0;
	}
	else if (str[data->i] == '|')
	{
		data->k += 1;
		data->j = 0;
	}
	else if (str[data->i] == '<')
	{
		data->k += 1;
		data->j = 0;
	}
}
