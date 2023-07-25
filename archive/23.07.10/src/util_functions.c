/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:57:46 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/12 12:58:36 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_name(char *s1)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(s1))
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '=')
	{
		if(s1[i] != '\'' && s1[i] != '\"')
			j++;
		i++;
	}
	if (!(dst = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0' && s1[i] != '=')
	{	
		if(s1[i] == '\'' || s1[i] == '\"')
			i++;
		else
		{	
			dst[j] = s1[i];
			i++;
			j++;
		}		
	}
	dst[j] = '\0';
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

void	rewrite_shell_level(t_data *data)
{
	int			sh_level;
	char		*sh_level_str;
	t_env_list	*sh_lvl_var_sorted;
	t_env_list	*sh_lvl_var_unsorted;
	char		*shlvl = "SHLVL";
		
	sh_lvl_var_sorted = searchlist(data->env_sorted, shlvl);
	sh_level_str = sh_lvl_var_sorted->name;
	if (strcmp(sh_level_str, "") == 0)
		return ;	
}
