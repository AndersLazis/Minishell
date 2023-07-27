/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_smaller.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 15:29:13 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_smaller(char *str, t_data *data)
{
	data->lexer_output[data->k][data->j] = str[data->i];
	data->j += 1;
	data->i += 1;
	if (space(str[data->i]) == 1)
	{
		data->k += 1;
		data->j = 0;
		return ;
	}
	else if (character(str[data->i]) == 1)
	{
		if (data->k != 0)
			data->k += 1;
		data->j = 0;
		return ;
	}
	else if (str[data->i] == '|')
	{
		if (data->k != 0)
			data->k += 1;
		data->j = 0;
		return ;
	}
	else if (str[data->i] == '>')
	{
		if (data->k != 0)
			data->k += 1;
		data->j = 0;
		return ;
	}
	return ;
}