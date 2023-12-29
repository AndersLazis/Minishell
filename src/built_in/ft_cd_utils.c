/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:58:18 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/30 21:02:47 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* prints OLDPWD value */
int	print_oldpwd(t_data *data)
{
	t_env_list	*current;

	if (searchlist(data->env_sorted, "OLDPWD") != NULL)
	{
		current = searchlist(data->env_sorted, "OLDPWD");
		if (current->value)
			printf("%s\n", current->value);
		else
			printf("OLDPWD not set\n");
		return (EXIT_SUCCESS);
	}
	else
		printf("OLDPWD not set\n");
	return (EXIT_FAILURE);
}

/* frees env list node value */
int	free_list_value(t_env_list *list)
{
	if (list->value)
	{
		free(list->value);
		list->value = NULL;
	}
	return (0);
}

int	create_node_old_pwd(char *old_pwd_sorted, 
char *old_pwd_unsorted, t_data *data)
{
	create_old_pwd(data->env_sorted, old_pwd_sorted);
	create_old_pwd(data->env_unsorted, old_pwd_unsorted);
	sort_list(data->env_sorted);
	return (0);
}

/* creates new OLDPWD node in unsorted list */
t_env_list	*create_new_oldpwd_in_unsorted(t_data *data)
{
	char		*name;
	t_env_list	*pwd_list_unsorted;

	name = ft_strdup("OLDPWD");
	insert_at_end(data->env_unsorted, name, "", 1);
	pwd_list_unsorted = searchlist(data->env_unsorted, "OLDPWD");
	free(name);
	free(pwd_list_unsorted->value);
	return (pwd_list_unsorted);
}

int	oldpwd_update(char *old_pwd_sorted, char *old_pwd_unsorted, t_data *data)
{
	t_env_list	*pwd_list_sorted;
	t_env_list	*pwd_list_unsorted;

	if ((searchlist(data->env_sorted, "OLDPWD") != NULL))
	{
		pwd_list_sorted = searchlist(data->env_sorted, "OLDPWD");
		pwd_list_unsorted = searchlist(data->env_unsorted, "OLDPWD");
		free_list_value(pwd_list_sorted);
		if (pwd_list_unsorted != NULL)
			free_list_value(pwd_list_unsorted);
		else if (pwd_list_unsorted == NULL)
			pwd_list_unsorted = create_new_oldpwd_in_unsorted(data);
		pwd_list_sorted->value = ft_strdup(old_pwd_sorted);
		pwd_list_unsorted->value = ft_strdup(old_pwd_unsorted);
		return (EXIT_SUCCESS);
	}
	else
		create_node_old_pwd(old_pwd_sorted, old_pwd_unsorted, data);
	update_envp(data);
	return (EXIT_FAILURE);
}
