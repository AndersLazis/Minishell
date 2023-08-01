/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:31:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 18:56:44 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_countparts(char const *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (space(s[i]) == 1)
			i++;
		if ((space(s[i]) == 0) && s[i] != '\0')
			count++;
		while ((space(s[i]) == 0) && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*ft_mallocwords(char *str, t_data *data)
{
	char	*str_save;

	data->mw_j = 0;
	str_save = ft_calloc(1000, 1);
	while ((space(str[data->i]) == 0) && str[data->i] != 0)
	{
		while ((space(str[data->i]) == 0) && str[data->i] != '\'' 
			&& str[data->i] != '\"' && str[data->i] != 0)
		{
			str_save[data->mw_j] = str[data->i];
			data->mw_j++;
			data->i += 1;
		}
		if (str[data->i] == '\"')
			str_save = process_double_quote(str_save, str, data);
		if (str[data->i] == '\'')
			str_save = process_single_quote(str_save, str, data);
	}
	return (str_save);
}

static void	ft_free(char **strs, t_data *data)
{
	while ((data->j)-- > 0)
		free(strs[data->j]);
	free(strs);
}

char	**split_args(char *str, t_data *data)
{
	int		wordcount;
	char	**strs;

	data->i = 0;
	data->j = 0;
	wordcount = ft_countparts(str);
	strs = malloc((wordcount + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (str[data->i] != 0)
	{
		while (space(str[data->i]) == 1 && str[data->i] != 0)
			(data->i)++;
		if (str[data->i] == '\0')
			break ;
		strs[data->j] = ft_mallocwords(str, data);
		if (strs[data->j] == NULL)
		{
			ft_free(strs, data);
			return (NULL);
		}
		(data->j)++;
	}
	strs[data->j] = NULL;
	return (strs);
}
