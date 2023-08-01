/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:31:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 20:07:14 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_env_list_node(char **env, int i, t_env_list *head)
{
	char		*name;
	char		*value;
	int			equal_sign;

	name = ft_strdup_name(env[i]);
	value = ft_strdup_value(env[i]);
	equal_sign = check_equal_sign(env[i]);
	insert_at_end(head, name, value, equal_sign);
	if (name)
		free(name);
	if (value)
		free(value);
	return (0);
}

void	init_env_sorted(t_data *data, char **env)
{
	t_env_list	*head;
	int			i;

	head = malloc(sizeof(t_env_list));
	head->name = ft_strdup_name(env[0]);
	head->value = ft_strdup_value(env[0]);
	head->equal_sign = check_equal_sign(env[0]);
	head->next = NULL;
	i = 1;
	while (env[i] != 0)
	{
		fill_env_list_node(env, i, head);
		i++;
	}
	if (searchlist(head, "SHLVL") == NULL)
		insert_at_end(head, "SHLVL", "1", 1);
	if (searchlist(head, "OLDPWD") == NULL)
		insert_at_end(head, "OLDPWD", "", 0);
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
	head->equal_sign = check_equal_sign(env[0]);
	head->next = NULL;
	i = 1;
	while (env[i] != 0)
	{
		fill_env_list_node(env, i, head);
		i++;
	}
	if (searchlist(head, "SHLVL") == NULL)
		insert_at_end(head, "SHLVL", "1", 1);
	data->env_unsorted = head;
}

void	increment_shell_level(t_data *data)
{
	t_env_list	*sh_lvl_var_unsorted;
	t_env_list	*sh_lvl_var_sorted;
	static char	*shlvl = "SHLVL";
	int			sh_level;

	sh_lvl_var_unsorted = searchlist(data->env_unsorted, shlvl);
	sh_lvl_var_sorted = searchlist(data->env_sorted, shlvl);
	if ((sh_lvl_var_unsorted == NULL) || (sh_lvl_var_sorted == NULL))
		return ;
	sh_level = ft_atoi(sh_lvl_var_unsorted->value) + 1;
	if (sh_lvl_var_unsorted->value)
		free(sh_lvl_var_unsorted->value);
	if (sh_lvl_var_sorted->value)
		free(sh_lvl_var_sorted->value);
	sh_lvl_var_unsorted->value = ft_itoa(sh_level);
	sh_lvl_var_sorted->value = ft_itoa(sh_level);
	sh_lvl_var_unsorted->equal_sign = 1;
	sh_lvl_var_sorted->equal_sign = 1;
}
