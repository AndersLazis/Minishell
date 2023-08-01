/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_single_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/29 16:45:13 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fsm_helper(char *str, t_data *data);

void	fsm_single_quotes(char *str, t_data *data)
{
	data->lexer_output[data->k][data->j] = str[data->i];
	data->nb_single_quotes += 1;
	data->i += 1;
	data->j += 1;
	while (str[data->i] != '\'' && str[data->i] != 0)
	{
		data->lexer_output[data->k][data->j] = str[data->i];
		data->j += 1;
		data->i += 1;
	}
	fsm_helper(str, data);
}

static void	fsm_helper(char *str, t_data *data)
{
	if (str[data->i] == '\'')
	{
		data->nb_single_quotes += 1;
		data->lexer_output[data->k][data->j] = str[data->i];
		data->j += 1;
		data->i += 1;
	}
	if (str[data->i] == '|' || str[data->i] == '>' || str[data->i] == '<')
	{
		data->k += 1;
		data->j = 0;
	}
	else if (space(str[data->i]) == 1)
	{
		data->lexer_output[data->k][data->j] = str[data->i];
		data->j += 1;
	}
	return ;
}
