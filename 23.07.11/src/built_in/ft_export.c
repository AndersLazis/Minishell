/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/08 19:00:53 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_sorted_list(t_env_list *current)
{
	t_env_list *temp;

	temp = current;
	while(temp)
	{
		printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	ft_export(t_data *data)
{
	t_env_list	*current;
	char		*name;
	
	if (data->split[1] == NULL)
		print_sorted_list(data->env_sorted);
	else
	{
		if(!is_env_var_name_valid(data))
		{	
			printf("export: `%s': not a valid identifier\n", data->split[1]);
			return ;
		}
		name = ft_strdup_name(data->split[1]);
		if (searchlist(data->env_sorted, name) != NULL)
		{
			current = searchlist(data->env_sorted, name);
			current->value = ft_strdup_value(data->split[1]);
			current = searchlist(data->env_unsorted, name);
			current->value = ft_strdup_value(data->split[1]);
		}
		else
		{
			insert_at_end(data->env_sorted, ft_strdup_name(data->split[1]), ft_strdup_value(data->split[1]));
			data->env_sorted = sort_list(data->env_sorted);
			insert_at_end(data->env_unsorted, ft_strdup_name(data->split[1]), ft_strdup_value(data->split[1]));
		}
	}
}
