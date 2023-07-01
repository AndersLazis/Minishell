/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_unsorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:31:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/30 23:40:41 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*ft_strdup_name(char *s1)
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

static	char	*ft_strdup_value(char *s1)
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

int	init_env_unsorted(t_data *data, char **env)
{
	t_env	*new;
	t_env	*current;
	int		i;

	current = malloc(sizeof(t_env));
	if(!current)
		return(EXIT_FAILURE);
	current->name = ft_strdup_name(env[0]);
	current->value = ft_strdup_value(env[0]);
	current->next = NULL;
	data->env = current;
	i = 1;
	while(env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env));
		if(!new)
			return(EXIT_FAILURE);
		current->name = ft_strdup_name(env[i]);
		current->value = ft_strdup_value(env[i]);
		new->next = NULL;
		current->next = new;
		//printf(" %s", current->name);
		//printf("%s\n", current->value);
		// printf("%p\n", current->next);
		current = new;
		i++;
	}
	return(0);
}
