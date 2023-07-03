/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_unsorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:31:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/03 19:19:36 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_env_unsorted(t_data *data, char **env)
{
	t_env	*new;
	t_env	*current;
	int		i;

	current = malloc(sizeof(t_env));
	if(!current)
		return(EXIT_FAILURE);
	current->name = ft_strdup_name(env[0]);
	current->value = ft_strdup_value(env[0]);
	current->next = NULL;
	data->env = current;
	i = 1;
	while(env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env));
		if(!new)
			return(EXIT_FAILURE);
		current->name = ft_strdup_name(env[i]);
		current->value = ft_strdup_value(env[i]);
		new->next = NULL;
		current->next = new;
		//printf(" %s", current->name);
		//printf("%s\n", current->value);
		// printf("%p\n", current->next);
		current = new;
		i++;
	}
	return(0);
}
