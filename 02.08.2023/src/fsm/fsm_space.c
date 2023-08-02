/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:32:38 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/02 00:17:06 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	character(char ch)
{
	if (ch <= 32 || ch > 126)
		return (0);
	if (ch == '>' || ch == '<')
		return (0);
	if (ch == '$' || ch == '|')
		return (0);
	if (ch == '\'' || ch == '\"')
		return (0);
	return (1);
}

int	space(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == ' ')
		return (1);
	else
		return (0);
}

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
