/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/08 19:19:38 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data)
{
	char	*name;
	
	if(data->split[1] == NULL)
		return ;
	else
	{
		if(!is_env_var_name_valid(data))
		{
			printf("UNSET: `%s': not a valid identifier\n", data->split[1]);
			return ;
		}
		else
		{
			name = ft_strdup_name(data->split[1]);
			if (searchlist(data->env_sorted, name) != NULL)
			{
				deletenode(data->env_sorted, name);
				deletenode(data->env_unsorted, name);
			}
		}
	}
}
