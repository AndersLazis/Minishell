/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:24:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 20:30:09 by mschulme         ###   ########.fr       */
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
