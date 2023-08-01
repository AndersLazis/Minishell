/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:31:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/28 15:31:06 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env_sorted(t_data *data, char **env)
{
	t_env_list	*head;
	char		*name;
	char		*value;
	int			equal_sign;
	int			i;

	head = malloc(sizeof(t_env_list));
	head->name = ft_strdup_name(env[0]);
	head->value = ft_strdup_value(env[0]);
	head->equal_sign = check_equal_sign(env[0]);	//<-changed_23.07.28
	head->next = NULL;
	i = 1;
	while (env[i] != 0)
	{
		name = ft_strdup_name(env[i]);
		value = ft_strdup_value(env[i]);
		equal_sign = check_equal_sign(env[i]);	//<-changed_23.07.28
		insert_at_end(head, name, value, equal_sign);	//<-changed_23.07.28
		free(name);
		free(value);
		i++;
	}
	if (searchlist(head, "SHLVL") == NULL)
		insert_at_end(head, "SHLVL", "1", 1);	//<-changed_23.07.28
	data->env_sorted = sort_list(head);
}

void	init_env_unsorted(t_data *data, char **env)
{
	t_env_list	*head;
	char		*name;
	char		*value;
	int			equal_sign;
	int			i;

	head = malloc(sizeof(t_env_list));
	if (!head)
		return ;
	head->name = ft_strdup_name(env[0]);
	head->value = ft_strdup_value(env[0]);
	head->equal_sign = check_equal_sign(env[0]);	//<-changed_23.07.28
	head->next = NULL;
	i = 1;
	while (env[i] != 0)
	{
		name = ft_strdup_name(env[i]);
		value = ft_strdup_value(env[i]);
		equal_sign = check_equal_sign(env[i]);	//<-changed_23.07.28
		insert_at_end(head, name, value, equal_sign);	//<-changed_23.07.28
		free(name);
		free(value);
		i++;
	}
	if (searchlist(head, "SHLVL") == NULL)
		insert_at_end(head, "SHLVL", "1", 1);	//<-changed_23.07.28
	data->env_unsorted = head;
}
