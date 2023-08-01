/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/30 23:16:27 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_sorted_list(t_env_list *current)
{
	t_env_list	*temp;

	temp = current;
	while (temp)
	{
		if ((temp->value == NULL || !ft_strcmp(temp->value, ""))
			&& temp->equal_sign == 0)
			printf("declare -x %s\n", temp->name);
		else if ((temp->value == NULL || !ft_strcmp(temp->value, ""))
			&& temp->equal_sign == 1)
			printf("declare -x %s=\"\"\n", temp->name);
		else
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	process_export(t_data *data)
{
	char		*name;
	char		*val;
	int			i;
	int			equal_sign;

	i = 1;
	while (data->split[i] != NULL)
	{
		name = ft_strdup_name(data->split[i]);
		val = ft_strdup_value(data->split[i]);
		equal_sign = check_equal_sign(data->split[i]);
		if ((searchlist(data->env_sorted, name) != NULL) 
			&& (ft_strcmp(val, "")))
			export_exist_variable(data, i);
		else
			export_new_variable(data, i);
		free(name);
		free(val);
		i++;
	}
}

void	export_exist_variable(t_data *data, int i)
{
	t_env_list	*current;
	char		*name;
	char		*val;
	int			equal_sign;

	name = ft_strdup_name(data->split[i]);
	val = ft_strdup_value(data->split[i]);
	equal_sign = check_equal_sign(data->split[i]);
	current = searchlist(data->env_sorted, name);
	current->value = ft_strdup_value(data->split[i]);
	current->equal_sign = check_equal_sign(data->split[i]);
	current = searchlist(data->env_unsorted, name);
	if (current != NULL)
	{
		current->value = ft_strdup_value(data->split[i]);
		current->equal_sign = check_equal_sign(data->split[i]);
	}
	else
		insert_at_end(data->env_unsorted, name, val, equal_sign);
	free(name);
	free(val);
}

void	export_new_variable(t_data *data, int i)
{
	char		*name;
	char		*val;
	int			equal_sign;

	name = ft_strdup_name(data->split[i]);
	val = ft_strdup_value(data->split[i]);
	equal_sign = check_equal_sign(data->split[i]);
	insert_at_end(data->env_sorted, name, val, equal_sign);
	data->env_sorted = sort_list(data->env_sorted);
	if (ft_strcmp(val, "") || (check_equal_sign(data->split[i]) == 1))
		insert_at_end(data->env_unsorted, name, val, equal_sign);
	free(name);
	free(val);
}

void	ft_export(t_data *data)
{
	if (data->split[1] == NULL)
		print_sorted_list(data->env_sorted);
	else
	{
		if (!is_env_var_name_valid(data->split, data, 1))
			return ;
		process_export(data);
		update_envp(data);
	}
}
