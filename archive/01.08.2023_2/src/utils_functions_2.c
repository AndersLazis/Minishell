/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:08:39 by aputiev           #+#    #+#             */
/*   Updated: 2023/08/01 20:08:55 by aputiev          ###   ########.fr       */
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
	dst = malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
		exit (EXIT_FAILURE);
	i = 0;
	while (s1[i] != '\0' && s1[i] != '=')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*return_null_value(void)
{
	char	*dst;

	dst = malloc(sizeof(char));
	if (dst == NULL)
		exit (EXIT_FAILURE);
	dst[0] = '\0';
	return (dst);
}

char	*my_strcp_value(char *s1, char *dst, int j)
{
	int	i;

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
	while (s1[j] != '=' && s1[j] != '\0')
		j++;
	if (s1[j] == '\0')
		return (return_null_value());
	j = j + 1;
	dst = malloc(sizeof(char) * ((i - j) + 1));
	if (dst == NULL)
		exit (EXIT_FAILURE);
	dst = my_strcp_value(s1, dst, j);
	return (dst);
}
