/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 00:13:05 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_home_directory(t_data *data)
{
	t_env_list	*current;

	if (searchlist(data->env_sorted, "HOME") != NULL)
	{
		current = searchlist(data->env_sorted, "HOME");
		if (chdir(current->value) == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
		printf("HOME not set\n");
	return (EXIT_FAILURE);
}

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

int	oldpwd_update(char *old_pwd_sorted, char *old_pwd_unsorted, t_data *data)
{
	t_env_list	*pwd_list_sorted;
	t_env_list	*pwd_list_unsorted;

	if ((searchlist(data->env_sorted, "OLDPWD") != NULL))
	{
		pwd_list_sorted = searchlist(data->env_sorted, "OLDPWD");
		pwd_list_unsorted = searchlist(data->env_unsorted, "OLDPWD");
		if (pwd_list_sorted->value)
		{
			free(pwd_list_sorted->value);
			pwd_list_sorted->value = NULL;
		}
		if (pwd_list_unsorted->value)
		{
			free(pwd_list_unsorted->value);
			pwd_list_unsorted->value = NULL;
		}
		pwd_list_sorted->value = ft_strdup(old_pwd_sorted);
		pwd_list_unsorted->value = ft_strdup(old_pwd_unsorted);
		return (EXIT_SUCCESS);
	}
	else
	{
		create_old_pwd(data->env_sorted, old_pwd_sorted);
		create_old_pwd(data->env_unsorted, old_pwd_unsorted);
		sort_list(data->env_sorted);
	}
	update_envp(data);
	return (EXIT_FAILURE);
}

int	ft_cd(t_data *data)
{
	int		exit_status;
	char	*old_pwd_sorted;
	char	*old_pwd_unsorted;

	exit_status = 0;
	printf("ft_cd: data->split[1]:|%s|\n", data->split[1]);
	if (data->split[1] == NULL)
		exit_status = go_home_directory(data);
	else if (!ft_strncmp(data->split[1], "-", 1))
		exit_status = print_oldpwd(data);
	else
	{
		old_pwd_sorted = getcwd(NULL, sizeof(NULL));
		old_pwd_unsorted = getcwd(NULL, sizeof(NULL));
		exit_status = chdir(data->split[1]);
		if (exit_status != 0)
			printf("No such file or directory\n");
		else
			oldpwd_update(old_pwd_sorted, old_pwd_unsorted, data);
	}
	if (exit_status != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
