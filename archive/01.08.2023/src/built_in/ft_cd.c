/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/30 21:03:07 by aputiev          ###   ########.fr       */
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

void	ft_cd(t_data *data)
{
	char	buf_unsorted[PATH_MAX];
	char	buf_sorted[PATH_MAX];

	data->exit_code = 0;
	if (data->split[1] == NULL)
		data->exit_code = go_home_directory(data);
	else if (!ft_strncmp(data->split[1], "-", 1))
		data->exit_code = print_oldpwd(data);
	else
	{
		getcwd(buf_unsorted, sizeof(buf_unsorted));
		getcwd(buf_sorted, sizeof(buf_sorted));
		data->exit_code = chdir(data->split[1]);
		if (data->exit_code != 0)
			perror(NULL);
		else
		{
			oldpwd_update(buf_sorted, buf_unsorted, data);
			currentpwd_update(data);
		}
	}
	if (data->exit_code < 0)
		data->exit_code *= -1;
}

/* updates PWD env var in sorted, unsorted lists and envp */
int	currentpwd_update(t_data *data)
{
	t_env_list	*pwd_list_sorted;
	t_env_list	*pwd_list_unsorted;

	if ((searchlist(data->env_sorted, "PWD") != NULL))
	{
		pwd_list_sorted = searchlist(data->env_sorted, "PWD");
		pwd_list_unsorted = searchlist(data->env_unsorted, "PWD");
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
		pwd_list_sorted->value = getcwd(NULL, sizeof(NULL));
		pwd_list_unsorted->value = getcwd(NULL, sizeof(NULL));
		update_envp(data);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
