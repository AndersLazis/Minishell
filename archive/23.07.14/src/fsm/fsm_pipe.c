/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/12 17:21:38 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_pipe(char *str, t_data *data)
{
	data->pipe_count += 1; // Add the more general cases
	data->lexer_output[data->k][data->j] = str[data->i];
	data->j += 1;
	data->i += 1;
	if (space(str[data->i]) == 1)
	{
		data->k += 1;
		data->j = 0;
		fsm_space(str, data);
	}
	else if (character(str[data->i]) == 1)
	{
		data->k += 1;
		data->j = 0;
		fsm_character(str, data);
	}
	else if (str[data->i] == '|')
		fsm_pipe(str, data);
	else if (str[data->i] == '>')
	{
		if (data->j > 0)
			data->k += 1;
		data->j = 0;
		fsm_greater(str, data);
	}
	else if (str[data->i] == '<')
	{
		if (data->j > 0)
			data->k += 1;
		data->j = 0;
		fsm_smaller(str, data);
	}
	else if (str[data->i] == '$')
		fsm_dollar(str, data);
	else if (str[data->i] == '\"')
		fsm_double_quotes(str, data);
	else if (str[data->i] == '\'')
		fsm_single_quotes(str, data);
	else if (str[data->i] == '\\')
		fsm_backslash(str, data);
	else if (str[data->i] == '\0')
		return ;
	return ;
}
