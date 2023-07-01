/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:27:48 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/01 14:52:06 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	current = data->env;
	while(current->next != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_data *data)
{
	t_env_sorted	*current;

	current = data->env_sorted;
	while(current->next != NULL)
	{
		printf("declare -x %s=%s\n", current->name, current->value);
		current = current->next;
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
