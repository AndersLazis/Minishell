/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/22 13:22:35 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data)
{
	char	*name;
	int		i;

	i = 1;
	if(data->split[1] == NULL)
		return ;
	else
	{
		while(data->split[i] != NULL)
		{
			if(!is_env_var_name_valid(data->split))
			{
				printf("unset:`%s': not a valid identifier\n", data->split[1]);
				return ;
			}
			else
			{
				name = ft_strdup_name(data->split[i]);
				if (searchlist(data->env_sorted, name) != NULL)
				{
					deletenode(data->env_sorted, name);
					deletenode(data->env_unsorted, name);
				}
				//free (name);
			}
			i++;
		}
	}
}
