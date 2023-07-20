/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/19 19:06:58 by aputiev          ###   ########.fr       */
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
		printf("%s\n", current->value);
		return(EXIT_SUCCESS);
	}
	else
		printf("OLDPWD not set\n");
	return(EXIT_FAILURE);	
}

/* updates OLDPWD env value */
int	oldpwd_update(char* old_pwd, t_data *data)
{	
	t_env_list	*PWD_list_sorted;
	t_env_list	*PWD_list_unsorted;

	if((searchlist(data->env_sorted, "OLDPWD") != NULL) && searchlist(data->env_unsorted, "OLDPWD") != NULL)
	{
		PWD_list_sorted = searchlist(data->env_sorted, "OLDPWD");
		PWD_list_unsorted = searchlist(data->env_unsorted, "OLDPWD");
		printf("%p\n",PWD_list_sorted->value);
		printf("%p\n",PWD_list_unsorted->value);
		printf("data->env_sorted:%p\n", data->env_sorted);
		printf("data->env_unsorted:%p\n", data->env_unsorted);


		
		free(PWD_list_sorted->value);
		free(PWD_list_unsorted->value);
		PWD_list_sorted->value = ft_strdup(old_pwd);
		PWD_list_unsorted->value = ft_strdup(old_pwd);
		return(EXIT_SUCCESS);
	}
	else
		insert_at_end(data->env_sorted, "OLDPWD", old_pwd);
		insert_at_end(data->env_unsorted, "OLDPWD", old_pwd);
		//sort_list(data->env_sorted);
		//update_envp(data);
		return(EXIT_FAILURE);	
}


int	ft_cd(t_data *data)		//<-changed_23.07.19
{	
	int		exit_status;
	char	*pathdirectory;
	char	*old_pwd;
	
	exit_status = 0;
	printf("ft_cd: data->split[1]:|%s|\n", data->split[1]);
	if (data->split[1] == NULL)
		exit_status = go_home_directory(data);	// 0 if ok, 1 if nok
	else if (!ft_strncmp(data->split[1], "-", 1))
		exit_status = print_oldpwd(data);	// 0 if ok, 1 if nok
	else
	{	
		old_pwd = getcwd(NULL, sizeof(NULL));
		printf("old_pwd:%s\n", old_pwd);
		exit_status = chdir(data->split[1]);	// 0 if ok, 1 if nok
		if(exit_status != 0)
			printf("cd error\n");
		oldpwd_update(old_pwd, data);	
		//pwd_update(data);
	}
	// free(old_pwd);
	if(exit_status != 0)
		return(EXIT_FAILURE);
	return(EXIT_SUCCESS);
}
	//if ()
	// else if (data->split[2] == NULL)
	// {	
	// 	getcwd(old_pwd, sizeof(old_pwd));
	// 	if(chdir(data->split[1]) == -1)
	// 		printf("No such file or directory\n");
	// 	else
	// 		{
	// 			printf("oldpwd:%s\n", old_pwd);
	// 			//update_oldpwd(data);
	// 		}
	// }
// 	else
// 	{
// 		printf("too many arguments\n");
// 	}
// }

// int	update_oldpwd(t_data *data)
// {
// 	t_env_list	*current;
// 	char		*name;
// 	char		*val;
// 	int			i;
	
// 	i= 1;	
// 		while (data->split[i] != NULL)
// 		{
// 			name = "OLDPWD";
// 			val = ft_strdup_value(data->split[i]);
// 			if (searchlist(data->env_sorted, name) != NULL)
// 			{
// 				current = searchlist(data->env_sorted, name);
// 				current->value = ft_strdup_value(data->split[i]);
// 				current = searchlist(data->env_unsorted, name);
// 				current->value = ft_strdup_value(data->split[i]);
// 			}
// 			else
// 			{
// 				insert_at_end(data->env_sorted, name, val);
// 				data->env_sorted = sort_list(data->env_sorted);
// 				insert_at_end(data->env_unsorted, name, val);
// 			}
// 			i++;
// 		}
	
// 	update_envp(data);	
