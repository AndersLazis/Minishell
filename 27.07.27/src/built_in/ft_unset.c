/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 16:20:08 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data)
{
	char	*name;
	int		i;

	i = 1;
	if (data->split[1] == NULL)
		return ;
	else
	{
		while (data->split[i] != NULL)
		{
			if (!is_env_var_name_valid(data->split, data))
			{
				printf("unset:`%s': not a valid identifier\n", data->split[1]);
				data->exit_code = 1;
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
			}
			i++;
		}
	}
	update_envp(data);
}
