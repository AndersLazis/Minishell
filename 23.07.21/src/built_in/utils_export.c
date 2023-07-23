/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:24:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 18:48:33 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_var_name_valid(char **split)
{
	int	i;
	int	j;
	
	j = 1;
	if(!split[1][0] || !split)
		return (0);		
	// printf("export: `%s': not a valid identifier\n", data->split[i]);
	while (split[j] != NULL)
	{
		i = 0;
		if(!ft_strcmp(split[j], "="))
		{
			printf("export: `%s': not a valid identifier\n", split[j]);
			return (0);
		}
		while(split[j][i] != '\0' && split[j][i] != '=')
		{			
			if ((split[j][0] != '_') && (!(split[j][0] >= 'a' && split[j][0] <= 'z')) && (!(split[j][0] >= 'A' && split[j][0] <= 'Z')))
			{	
				printf("export: `%s': not a valid identifier\n", split[j]);
				return (0);
			}				
			if ((split[j][i] != '_') && (split[j][i] < '0' && split[1][i] > '9') && (split[j][i] < 'a' && split[j][i] > 'z') && (split[j][i] < 'A' && split[j][i] > 'Z'))
			{	
				printf("export: `%s': not a valid identifier\n", split[j]);
				return (0);
			}
			i++;			
		}
		// if(split[j][i] == '=')
		// i++;		
		j++;
	}
	return (1);
}

// int	is_env_var_val_valid(t_data *data)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	j = 1;
// 	if(!data->split[1][i])		
// 		return (0);
// 	while (data->split[j] != NULL)
// 	{	
// 		i = 0;
// 		while(data->split[j][i] != '\0' && data->split[j][i] != '=')
// 			i++;
// 		if(data->split[j][i] == '=')
// 			i++;
// 		while(data->split[1][i] != '\0')
// 		{
// 			if ((data->split[1][0] != '_' && data->split[1][0] != 34 && data->split[1][0] != 39) && (!(data->split[1][0] >= 'a' && data->split[1][0] <= 'z')) && (!(data->split[1][0] >= 'A' && data->split[1][0] <= 'Z')))
// 				return (0);
// 			if ((data->split[1][i] != '_' && data->split[1][0] != 34 && data->split[1][0] != 39) && (data->split[1][i] < '0' && data->split[1][i] > '9') && (data->split[1][i] < 'a' && data->split[1][i] > 'z') && (data->split[1][i] < 'A' && data->split[1][i] > 'Z'))
// 				return (0);
// 			i++;
// 		}
// 		j++;
// 	}
// 	return (1);
// }
