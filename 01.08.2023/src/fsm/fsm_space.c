/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:32:38 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 18:02:06 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_space(char *str, t_data *data)
{
	data->i += 1;
	if (str[data->i] == '|')
	{
		if (data->j > 0)
			data->k += 1;
		data->j = 0;
	}
	else if (str[data->i] == '>')
	{
		if (data->j > 0)
			data->k += 1;
		data->j = 0;
	}
	else if (str[data->i] == '<')
	{
		if (data->j > 0)
			data->k += 1;
		data->j = 0;
	}
}
