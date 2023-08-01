/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:27:48 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/28 14:40:41 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*//////////////INCLUDES/////////////*/
#include "minishell.h"
#include <limits.h>



typedef struct s_env
{
    char            *name;	
    char            *value;	
    struct  s_env   *next;
    
}   t_env;

typedef struct s_data
{
	t_env	*env;
	t_env	*env_sorted;
	char	**envp;   
	
}   t_data;

t_data data;

char	*ft_strdup_name(char *s1)
{
	int		i;
	char	*dst;

	i = 0;
	if (!(s1))
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '=')
		i++;
	if (!(dst = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && s1[i] != '=')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_value(char *s1)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	if (!(s1))
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s1[j] != '=' || s1[i] != '\0')
		j++;
	j = j + 1;
	if (!(dst = malloc(sizeof(char) * ((i-j) + 1))))
		return (NULL);
	i = 0;
	while (s1[j] != '\0')
	{
		dst[i] = s1[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	//printf("DST:%s\n", dst);
	return (dst);
}

//////////////////////////////////////////

/* environment initialization */
int	init_env(char **envp)
{
	t_env	*new;
	t_env	*current;
	int	i;

	current = malloc(sizeof(t_env));
	if(!current)
		return(1);
	current->name = ft_strdup_name(envp[0]);	
	current->value = ft_strdup_value(envp[0]);
	current->next = NULL;	
	data.env = current;
	i = 1;	
	while(envp && envp[0] && envp[i])
	{	
		new = malloc(sizeof(t_env));
		if(!new)
			return(1);
		current->name = ft_strdup_name(envp[i]);
		current->value = ft_strdup_value(envp[i]);
		new->next = NULL;
		current->next = new;
		// printf(" %s", current->name);	
		// printf("%s\n", current->value);		
		// printf("%p\n", current->next);
		current = new;
		i++;	
	}
	return(0);		
}

int	pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf)) != NULL))
		return (-1);
	return 0;
}

/* env command */
int	ft_env(char **envp)
{
	int	i;
	char	*env_var;
	
	i = 0;
	env_var = envp[i];
	while(env_var != NULL)
	{
		printf("%s\n", env_var);
		i++;
		env_var = envp[i];
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

t_env	*sort_list(t_env *lst, int	(*ft_strcmp)(char *s1, char *s2))
{
	char	*swap_val;
	char	*swap_name;
	t_env	*tmp;

	tmp = lst;
	while(lst->next != NULL)
	{
		if (((*ft_strcmp)(lst->name, lst->next->name)) > 0)
		{	/*ERROR IS HERE*/
			//swap_name = lst->name;
			swap_val = lst->value;
			//lst->name = lst->next->name;
			lst->value = lst->next->value;
			//lst->next->name = swap_name;
			lst->next->value = swap_val;			
			lst = tmp;
		}
		else
		{	
			lst = lst->next;
		}
	}
	lst = tmp;
	return (lst);
}

int	init_env_sorted(char **envp)
{
	t_env	*new;
	t_env	*current;
	int	i;

	current = malloc(sizeof(t_env));
	if(!current)
		return(1);
	current->name = ft_strdup_name(envp[0]);
	current->value = ft_strdup_value(envp[0]);	
	current->next = NULL;	
	data.env_sorted = current;
	i = 1;
	while(envp && envp[0] && envp[i])
	{	
		new = malloc(sizeof(t_env));
		if(!new)
			return(1);
		current->name = ft_strdup_name(envp[i]);
		current->value = ft_strdup_value(envp[i]);
		new->next = NULL;
		current->next = new;
		// printf(" %s", current->name);	
		// printf("%s\n", current->value);		
		// printf("%p\n", current->next);
		current = new;
		i++;	
	}
	 return(0);		
}

int ft_print_sorted_env(char **envp)
{
	init_env_sorted(envp);
	data.env_sorted = sort_list(data.env_sorted, (*ft_strcmp));

	////////////
	
	t_env	*current;
	int	i;

	current = data.env_sorted;
	while(current->next != NULL)
	{	
		// printf("declare -x %s", current->name);
		// write(1, "=", 1);
		// printf("%s\n", current->value);
		current = current->next;
	}

	/////////////////	
	return(0);
}





int ft_export(char **envp)
{
	int	i;
	t_env *current;
	

		ft_print_sorted_env(envp);

	// else
	// current = data.env;
	// while(current->next != NULL)
	// {
	// 	printf("declare -x %s\n", current->value);
	// 	current = current->next;
	// }
	
	// i = 1;
	// // while(args[i] != NULL)
	// // {
	// // 	printf("%s\n", args[i]);
	// // 	i++;
	// // }
	return (0);
}