/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:57:46 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/08 21:32:57 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_name(char *s1)
{
	char	*dst;
	int		i;

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
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(s1))
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s1[j] != '=' || s1[i] != '\0')
		j++;
	j = j + 1;
	if (!(dst = malloc(sizeof(char) * ((i - j) + 1))))
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

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return 0;
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
