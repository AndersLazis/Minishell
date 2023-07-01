/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:12:26 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/01 14:52:27 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_operator(char ch, char ch1)
{
	if (ch == '$')
		return (1);
	if (ch == '>' && ch1 == '>')
		return (1);
	if (ch == '<' && ch1 == '<')
		return (1);
	if (ch == '|' || ch == '>' || ch == '<')
		return (1);
	if (ch == '~' && ch1 == '/')
		return (1);
	return (0);
}

static int	is_space(int ch)
{
	if (ch == ' ' || (ch >= 9 && ch <= 13))
		return (1);
	else
		return (0);
}

char	**lexer(char *str, char **lexer_output, t_data *data)
{
	int		i;
	int		j;
	int		k;
	size_t	h;
	
	i = 0;
	j = 0;
	k = 0;
	h = 0;
	lexer_output = malloc((ft_strlen(str) + 1) * sizeof(char*));
	
	while (h < ft_strlen(str))
	{
		lexer_output[h] = malloc(ft_strlen(str) + 1);
		h++;
	}
	while (str[i] != 0)
	{
		if (is_operator(str[i], str[i + 1]) == 1 && str[i] != 0)
		{
			lexer_output[j][0] = str[i];
			i++;
			k = 1;
		}
		while (is_operator(str[i], str[i + 1]) == 0 && str[i] != 0)
		{
			lexer_output[j][k] = str[i];
			i++;
			k++;
		}
		if (is_operator(str[i], str[i + 1]) == 1 && str[i] != 0)
		{
			lexer_output[j][k] = 0;
			j++;
			lexer_output[j][0] = str[i];
			k = 1;
		}
		i++;
	}
	lexer_output[j + 1] = NULL;
	lexer_output = expander(lexer_output, data);
	return (lexer_output);
}
