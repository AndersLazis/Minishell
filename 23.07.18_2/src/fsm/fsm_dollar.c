/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 16:31:35 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_dollar(char *str, t_data *data)
{
	dollarsignexpansion(str, data);
	if (space(str[data->i]) == 1)
	{
		data->lexer_output[data->k][data->j] = str[data->i];
		data->j += 1;
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
	else if (str[data->i] == '<')
	{
		if (data->k != 0)
			data->k += 1;
		data->j = 0;
		return ;
	}
	return ;
}
