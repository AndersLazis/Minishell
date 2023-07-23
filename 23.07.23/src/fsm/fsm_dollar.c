/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/22 21:48:02 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_dollar(char *str, t_data *data)
{
	data->helper_dollar = 0;
	dollarsignexpansion(str, data);
	if (str[data->i] == '|' || str[data->i] == '>' || str[data->i] == '<')
	{
		data->k += 1;
		data->j = 0;
	}
	else if (space(str[data->i]) == 1)
	{
		data->lexer_output[data->k][data->j] = str[data->i];
		if (data->helper_dollar == -1)
			return ;
		data->j += 1;
	}
}
