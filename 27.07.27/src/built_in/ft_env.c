/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/24 23:49:51 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)
{
	t_env_list	*current;

	current = data->env_unsorted;
	while (current)
	{
		if (current->value == NULL)
			printf("%s=%s\n", current->name, "\"\"");
		else
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}