/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_double_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 15:52:40 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_double_quotes(char *str, t_data *data)
{
	data->lexer_output[data->k][data->j] = str[data->i];
	data->j += 1;
	data->i += 1;
	data->nb_double_quotes += 1;
	while (str[data->i] != '\"' && str[data->i] != 0)
	{
		if (str[data->i] == '$')
			dollarsignexpansion(str, data);
		else
		{
			data->lexer_output[data->k][data->j] = str[data->i];
			data->j += 1;
			data->i += 1;
		}
	}
	if (str[data->i] == '\"')
	{
		data->lexer_output[data->k][data->j] = str[data->i];
		data->j += 1;
		data->i += 1;
		data->nb_double_quotes += 1;
	}
	if (space(str[data->i]) == 1)
	{
		data->lexer_output[data->k][data->j] = str[data->i];
		data->j += 1;
		return ;
	}
	else if (str[data->i] == '|')
	{
		data->k += 1;
		data->j = 0;
		return ;
	}
	else if (str[data->i] == '>')
	{
		data->k += 1;
		data->j = 0;
		return ;
	}
	else if (str[data->i] == '<')
	{
		data->k += 1;
		data->j = 0;
		return ;
	}
	return ;
}
