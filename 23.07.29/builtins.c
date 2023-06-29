/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:27:48 by aputiev           #+#    #+#             */
/*   Updated: 2023/06/29 21:41:30 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*//////////////INCLUDES/////////////*/
#include "minishell.h"
#include <limits.h>



typedef struct s_env
{
    char            *value;
    struct  s_env   *next;
    
}   t_env;

typedef struct s_data
{
	t_env	*env;
	char	**envp;   
}   t_data;

t_data data;

/////////////////////////////////////////
// int	main(int ac, char **av, char **envp)
// {	
// 	init_env(envp);
// 	//env(envp);
// 	return (0);
// }
//////////////////////////////////////////

/* environment initialization */
int	init_env(char **envp)
{
	t_env	*env = NULL;
	t_env	*current;
	int	i;

	i = 0;	
	env = malloc(sizeof(t_env));
	if(!env)
		return(1);
	data.env = env;
	data.envp = envp;
	env->value = envp[i];
	env->next = NULL;	

	while(envp[i] != NULL)
	{	
		current = current->next;
		current = malloc(sizeof(t_env));
		env->next = current;
		current->value = envp[i];
		current->next = NULL;
		printf("%s\n", current->value);
		printf("%p\n", current->next);	
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

int ft_export(char **args)
{
	int	i;
	t_env *current;
	
	// if(!args[1])
	// {
	// 	ft_env(data.envp);
	// 	return(0);
	// }
	current = data.env;
	while(current->next != NULL)
	{
		printf("declare -x %s\n", current->value);
		current = current->next;
	}
	
	i = 1;
	// while(args[i] != NULL)
	// {
	// 	printf("%s\n", args[i]);
	// 	i++;
	// }
	return (0);
}