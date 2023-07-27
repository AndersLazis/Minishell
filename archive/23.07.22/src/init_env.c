/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:31:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/15 20:34:10 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env_sorted(t_data *data, char **env)
{
	t_env_list	*head;
	int			i;

	head = malloc(sizeof(t_env_list));
	head->name = ft_strdup_name(env[0]);
	head->value = ft_strdup_value(env[0]);
	head->next = NULL;
	i = 1;
	while (env[i] != 0)
	{
		insert_at_end(head, ft_strdup_name(env[i]), ft_strdup_value(env[i]));
		i++;
	}
	if (searchlist(head, "SHLVL") == NULL)
		insert_at_end(head, "SHLVL", "1");
	data->env_sorted = sort_list(head);
}

void	init_env_unsorted(t_data *data, char **env)
{
	t_env_list	*head;
	int			i;

	head = malloc(sizeof(t_env_list));
	if (!head)
		return ;
	head->name = ft_strdup_name(env[0]);
	head->value = ft_strdup_value(env[0]);
	head->next = NULL;
	i = 1;
	while (env[i] != 0)
	{
		insert_at_end(head, ft_strdup_name(env[i]), ft_strdup_value(env[i]));
		i++;
	}
	if (searchlist(head, "SHLVL") == NULL)
		insert_at_end(head, "SHLVL", "1");
	data->env_unsorted = head;
}