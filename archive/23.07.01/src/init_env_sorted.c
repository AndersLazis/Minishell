/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:31:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/01 14:52:20 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (dst);
}

static int	ft_strcmp(char *s1, char *s2)
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

void	swap(int envc, char **env)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < envc)
	{
		j = 0;
		while (j <  envc - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	init_env_sorted(t_data *data, char **env)
{
	t_env_sorted	*new;
	t_env_sorted	*current;
	int				i;
	
	i = 0;
	while(env[i])
		i++;
	swap(i, env);
	current = malloc(sizeof(t_env_sorted));
	if(!current)
		return(EXIT_FAILURE);
	current->name = ft_strdup_name(env[0]);
	current->value = ft_strdup_value(env[0]);
	current->next = NULL;
	data->env_sorted = current;
	i = 1;
	while(env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env_sorted));
		if(!new)
			return(EXIT_FAILURE);
		current->name = ft_strdup_name(env[i]);
		current->value = ft_strdup_value(env[i]);
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