/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:29:58 by aputiev           #+#    #+#             */
/*   Updated: 2023/08/01 19:30:14 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*process_double_quote(char *str_save, char *str, t_data *data)
{
	data->i += 1;
	while (str[data->i] != '\"' && str[data->i] != 0)
	{
		str_save[data->mw_j] = str[data->i];
		data->mw_j++;
		data->i += 1;
	}
	data->i += 1;
	return (str_save);
}

char	*process_single_quote(char *str_save, char *str, t_data *data)
{
	data->i += 1;
	while (str[data->i] != '\'' && str[data->i] != 0)
	{
		if (str[data->i] != '\'')
			str_save[data->mw_j] = str[data->i];
		data->mw_j++;
		data->i += 1;
	}
	data->i++;
	return (str_save);
}
