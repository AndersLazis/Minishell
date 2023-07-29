/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/29 17:17:07 by aputiev          ###   ########.fr       */
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

int	oldpwd_update(char *old_pwd_sorted, char *old_pwd_unsorted, t_data *data)	//<-changed_23.07.29
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
		if(pwd_list_unsorted != NULL)
		{
			if (pwd_list_unsorted->value)
			{
				free(pwd_list_unsorted->value);
				pwd_list_unsorted->value = NULL;
			}
		}
		else if (pwd_list_unsorted == NULL)
		{	
			char *name = strdup("OLDPWD");
			insert_at_end(data->env_unsorted, name, "", 1);
			pwd_list_unsorted = searchlist(data->env_unsorted, "OLDPWD");
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

int	currentpwd_update(t_data *data)	//<- changed_23.07.27_2
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

void    ft_cd(t_data *data)
{
    char    buf_unsorted[PATH_MAX];
    char    buf_sorted[PATH_MAX];
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