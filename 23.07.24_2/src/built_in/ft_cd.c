/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/22 13:16:27 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Changes directory to HOME directory ("cd-no-args" case) */
int	go_home_directory(t_data *data)
{
	t_env_list	*current;
	if(searchlist(data->env_sorted, "HOME") != NULL)
	{
		current = searchlist(data->env_sorted, "HOME");
		if(chdir(current->value) == -1)
			return(EXIT_FAILURE);
		return(EXIT_SUCCESS);
	}
	else
		printf("HOME not set\n");
	return(EXIT_FAILURE);	
}

/* prints OLDPWD directory ("cd-" case) */
int	print_oldpwd(t_data *data)
{
	t_env_list	*current;
	if(searchlist(data->env_sorted, "OLDPWD") != NULL)
	{
		current = searchlist(data->env_sorted, "OLDPWD");
		
		if (current->value)
			printf("%s\n", current->value);
		else
			printf("OLDPWD not set\n");
		return(EXIT_SUCCESS);
	}
	else
		printf("OLDPWD not set\n");
	return(EXIT_FAILURE);	
}



// static void	print_list(t_env_list *current)
// {
// 	t_env_list *temp;

// 	temp = current;
// 	while(temp)
// 	{	
// 		if(current->value == NULL)
// 			printf("%s=%s\n", current->name, "\"\"");
// 		else
// 			printf("declare -x %s|%p|\n", temp->name, temp->value);
// 		temp = temp->next;
// 	}
// }

/* updates OLDPWD env value */
int	oldpwd_update(char* old_pwd_sorted, char* old_pwd_unsorted, t_data *data)
{	
	t_env_list	*PWD_list_sorted;
	t_env_list	*PWD_list_unsorted;

	
	if((searchlist(data->env_sorted, "OLDPWD") != NULL) && searchlist(data->env_unsorted, "OLDPWD") != NULL)
	{
		PWD_list_sorted = searchlist(data->env_sorted, "OLDPWD");
		PWD_list_unsorted = searchlist(data->env_unsorted, "OLDPWD");
		printf("%p\n",PWD_list_sorted->value);
		printf("%p\n",PWD_list_unsorted->value);
		if(PWD_list_sorted->value)
		{	
			free(PWD_list_sorted->value);
			PWD_list_sorted->value = NULL;
		}
		if(PWD_list_unsorted->value)
		{
			free(PWD_list_unsorted->value);
			PWD_list_unsorted->value = NULL;
		}
		PWD_list_sorted->value = ft_strdup(old_pwd_sorted);
		PWD_list_unsorted->value = ft_strdup(old_pwd_unsorted);
		return(EXIT_SUCCESS);
	}
	else
		create_old_pwd(data->env_sorted, old_pwd_sorted);
		create_old_pwd(data->env_unsorted, old_pwd_unsorted);
		sort_list(data->env_sorted);
		update_envp(data);
		return(EXIT_FAILURE);	
}


int	ft_cd(t_data *data)
{	
	int		exit_status;
	//char	*pathdirectory;	//<-changed_22.07.23
	char	*old_pwd_sorted;
	char	*old_pwd_unsorted;
	
	exit_status = 0;
	printf("ft_cd: data->split[1]:|%s|\n", data->split[1]);
	if (data->split[1] == NULL)
		exit_status = go_home_directory(data);	// 0 if ok, 1 if nok
	else if (!ft_strncmp(data->split[1], "-", 1))
		exit_status = print_oldpwd(data);	// 0 if ok, 1 if nok
	else
	{	
		old_pwd_sorted = getcwd(NULL, sizeof(NULL));
		old_pwd_unsorted = getcwd(NULL, sizeof(NULL));
		// printf("old_pwd:%s\n", old_pwd_sorted, old_pwd_unsorted);
		exit_status = chdir(data->split[1]);	// 0 if ok, 1 if nok
		if(exit_status != 0)
			printf("No such file or directory\n");
		else
			oldpwd_update(old_pwd_sorted, old_pwd_unsorted, data);	
		//pwd_update(data);
	}
	// free(old_pwd);
	if(exit_status != 0)
		return(EXIT_FAILURE);
	return(EXIT_SUCCESS);
}
