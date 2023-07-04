/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:27:48 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/04 21:33:40 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_env(char **env)
{
	int i = 0;
	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf)) != NULL))
		return (-1);
	printf("%s\n", buf);
	return 0;
}

int	ft_env(t_data *data)
{
	t_env *current;
	print_env(data->envp);
	current = data->env;
	while(current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int		is_env_var_name_valid(char *args)
{
	int	i;
	int	quotes;
	int	double_quotes;
	i = 0;

	while(args[i] != '\0' && args[i] != '=')
	{
		if ((args[0] != '_' && args[0] != 34 && args[0] != 39) && (!(args[0] > 'a' && args[0] < 'z')) && (!(args[0] > 'A' && args[0] < 'Z')))
			return (0);
		if ((args[i] != '_' && args[0] != 34 && args[0] != 39) && (args[i] < '0' && args[i] > '9') && (args[i] < 'a' && args[i] > 'z') && (args[i] < 'A' && args[i] > 'Z'))
			return (0);
		i++;
	}
	return (1);
}

int		is_quotes_are_closed(char *args)
{	
	int	i;
	int	quotes;
	int	double_quotes;
	i = 0;
	quotes = 0;
	double_quotes = 0;
	while(args[i] != '\0')
	{
		if (args[i] == 39)
			quotes++;
		if (args[i] == 34)
			double_quotes++;
		i++;
	}
	if (quotes%2 || double_quotes%2)
		return (0);
	return (1);
}


t_env_sorted *is_env_var_exist(char *args,t_data *data)
{	
	int	i;
	int	j;
	t_env_sorted *current;

	current = data->env_sorted;	
	while(current->next != NULL)
	{	
		i = 0;
		j = 0;
		while(args[i] == ' ' || args[i] == '\'' || args[i] == '\"' || args[i] == '\t')
			i++;
		while(args[i] != '\0' && args[i] != '=')
		{			
			if(current->name[j] != args[i])				
				break;
			i++;
			j++;
		}
		if(args[i] == '\0' || args[i] == '=')
			return(current);
		current=current->next;
	}
	return(NULL);
}

/* adds new environment variable into the unsorted list*/
int add_new_env_var_in_unsorted(char *args, t_data *data)
{	
	t_env	*current;
	t_env	*new;
	
	current = data->env;	
	while(current->next != NULL)	
		current=current->next;
	new = malloc(sizeof(t_env));
	current->next = new;
	new->next = NULL;
	new->name = ft_strdup_name(args);
	new->value = ft_strdup_value(args);
	current = data->env;	
	while(current != NULL)	
		current=current->next;
	return(0);
}

//export XX=5

/* adds new environment variable into the sorted list*/
int add_new_env_var_in_sorted(char *args,t_data *data)
{	
	t_env_sorted	*current;
	t_env_sorted	*new;

	char	*name = ft_strdup_name(args);
	char	*value = ft_strdup_value(args);
		
	current = data->env_sorted;
	
	while(current->next != NULL)
	{
		if((strcmp(name, current->name) > 0) && (strcmp(name, current->next->name) < 0))
		{
			new = malloc(sizeof(t_env_sorted));
			new->next = current->next;
			current->next = new;
			new->name = ft_strdup_name(args);
			new->value = ft_strdup_value(args);			
		}	
		current=current->next;
	}
	return(0);
}

/* Prints sorted list */
int print_sorted_list(t_data *data)
{
	t_env_sorted	*current;

	current = data->env_sorted;
	while(current->next != NULL)
	{
		printf("declare -x %s=\"%s\"\n", current->name, current->value);			
		current = current->next;
	}
	return (0);
}

int	rewrite_exist_env_var(char *args,t_data *data)
{
	
	return (0);
}

int	ft_export(char *args,t_data *data)
{
	t_env_sorted	*current;
	int errno;
	
	errno = 0;
	current = data->env_sorted;
	printf("=====export_args=====:%s\n", args); //<---Check input arguments to export function (for test purposes);
	if(!args)
	{
		print_sorted_list(data);
		printf("test");
	}
	else
	{
		if(!is_env_var_name_valid(args))
		{	
			printf("export: `%s': not a valid identifier\n", args);
			return (EXIT_FAILURE);
		}
		if(!is_quotes_are_closed(args))
		{	
			printf("minishell: printf: `%s': invalid format character\n", args);
			return (EXIT_FAILURE);
		}
		if(is_env_var_exist(args, data) == NULL)
		{
			add_new_env_var_in_sorted(args, data);
			add_new_env_var_in_unsorted(args, data);
		}
		else
			rewrite_exist_env_var(args, data);
		//print_sorted_list(data); //<---for testing purposes
	}	
	return (EXIT_SUCCESS);
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

