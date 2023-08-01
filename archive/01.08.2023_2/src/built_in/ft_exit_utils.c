/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:11:42 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/30 21:11:55 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_unsorted_list(t_data *data)
{
	t_env_list	*current;
	t_env_list	*ptr;

	current = data->env_unsorted;
	while (current)
	{
		ptr = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = ptr;
	}
	return (1);
}

int	free_sorted_list(t_data *data)
{
	t_env_list	*current;
	t_env_list	*ptr;

	current = data->env_sorted;
	while (current)
	{
		ptr = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = ptr;
	}
	return (1);
}
