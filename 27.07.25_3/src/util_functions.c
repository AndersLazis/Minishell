/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:57:46 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 18:55:19 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trimwhitespace(char *str)
{
	char	*end;

	while (space(*str))
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && space(*end))
		end--;
	end[1] = '\0';
	return (str);
}

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
	dst = malloc(sizeof(char) * ((i - j) + 1));
	if (dst == NULL)
		exit (EXIT_FAILURE);
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
		return (0);
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	increment_shell_level(t_data *data)
{
	t_env_list	*sh_lvl_var_unsorted;
	t_env_list	*sh_lvl_var_sorted;
	static char	*shlvl = "SHLVL";
	int			sh_level;

	sh_lvl_var_unsorted = searchlist(data->env_unsorted, shlvl);
	sh_lvl_var_sorted = searchlist(data->env_sorted, shlvl);
	if ((sh_lvl_var_unsorted == NULL) || (sh_lvl_var_sorted == NULL))
		return ;
	sh_level = ft_atoi(sh_lvl_var_unsorted->value) + 1;
	if (sh_lvl_var_unsorted->value)
		free(sh_lvl_var_unsorted->value);
	if (sh_lvl_var_sorted->value)
		free(sh_lvl_var_sorted->value);
	sh_lvl_var_unsorted->value = ft_itoa(sh_level);
	sh_lvl_var_sorted->value = ft_itoa(sh_level);
}
