/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/28 18:17:16 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)	//<-changed_23.07.28
{
	t_env_list	*current;

	current = data->env_unsorted;
	while (current)
	{
		if ((current->value == NULL || !ft_strcmp(current->value, "")) && current->equal_sign == 1)
			printf("%s=\n", current->name);
		else if ((current->value != NULL || ft_strcmp(current->value, "")) && current->equal_sign == 1)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}