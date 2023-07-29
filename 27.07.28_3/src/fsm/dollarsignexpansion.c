/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsignexpansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/28 22:37:51 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dollarsignexpansion(char *str, t_data *data)
{
	char		*str_exitcode;
	t_env_list	*current;
	char		*word;
	int			m;

	str_exitcode = NULL;
	word = ft_calloc(1000, 1);
	if (word == NULL)
	{
		printf("malloc error");
		exit (EXIT_FAILURE);
	}
	data->i += 1;
	if (str[data->i] == '?')
	{
		m = 0;
		str_exitcode = ft_itoa(data->exit_code);
		while (str_exitcode[m] != 0)
		{
			data->lexer_output[data->k][data->j] = str_exitcode[m];
			data->j += 1;
			m++;
		}
		data->i += 1;
		free(str_exitcode);
		free(word);
		return ;
	}
	if (space(str[data->i]) == 1 || str[data->i] == '"' ||str[data->i] == 0)
	{
		data->lexer_output[data->k][data->j] = '$';
		data->j += 1;
		free(word);
		return ;
	}
	if (str[data->i] == '$')
	{
		m = 0;
		str_exitcode = ft_itoa(69420);
		while (str_exitcode[m] != 0)
		{
			data->lexer_output[data->k][data->j] = str_exitcode[m];
			data->j += 1;
			m++;
		}
		data->i += 1;
		free(str_exitcode);
		free(word);
		return ;
	}
	m = 0;
	while (character(str[data->i]) == 1)
	{
		word[m] = str[data->i];
		data->i += 1;
		m++;
	}
	current = searchlist(data->env_sorted, word);
	if (current != NULL)
	{
		ft_strlcpy(word, current->value, 1000);
		m = 0;
		while (word[m] != 0)
		{
			data->lexer_output[data->k][data->j] = word[m];
			data->j += 1;
			m++;
		}
	}
	if (current == NULL && data->j == 0)
		data->helper_dollar = -1;
	free(str_exitcode);
	free(word);
}
