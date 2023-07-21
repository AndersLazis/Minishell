/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:24:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 16:27:28 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_var_name_valid(t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	if(!data->split[1][i])
		return (0);
	while (data->split[j] != NULL)
	{
		i = 0;
		while(data->split[j][i] != '\0' && data->split[j][i] != '=')
		{
			if ((data->split[1][0] != '_' && data->split[1][0] != 34 && data->split[1][0] != 39) && (!(data->split[1][0] >= 'a' && data->split[1][0] <= 'z')) && (!(data->split[1][0] >= 'A' && data->split[1][0] <= 'Z')))
				return (0);
			if ((data->split[1][i] != '_' && data->split[1][0] != 34 && data->split[1][0] != 39) && (data->split[1][i] < '0' && data->split[1][i] > '9') && (data->split[1][i] < 'a' && data->split[1][i] > 'z') && (data->split[1][i] < 'A' && data->split[1][i] > 'Z'))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	is_env_var_val_valid(t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	if(!data->split[1][i])		
		return (0);
	while (data->split[j] != NULL)
	{	
		i = 0;
		while(data->split[j][i] != '\0' && data->split[j][i] != '=')
			i++;
		if(data->split[j][i] == '=')
			i++;
		while(data->split[1][i] != '\0')
		{
			if ((data->split[1][0] != '_' && data->split[1][0] != 34 && data->split[1][0] != 39) && (!(data->split[1][0] >= 'a' && data->split[1][0] <= 'z')) && (!(data->split[1][0] >= 'A' && data->split[1][0] <= 'Z')))
				return (0);
			if ((data->split[1][i] != '_' && data->split[1][0] != 34 && data->split[1][0] != 39) && (data->split[1][i] < '0' && data->split[1][i] > '9') && (data->split[1][i] < 'a' && data->split[1][i] > 'z') && (data->split[1][i] < 'A' && data->split[1][i] > 'Z'))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}
