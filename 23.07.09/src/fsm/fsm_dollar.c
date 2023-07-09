/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/08 22:04:01 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_dollar(char *str, t_data *data)
{
	t_env_list *current;
	char *word;
	int m;

	m = 0;
	word = malloc(1000 * sizeof(char*));
	(data->i)++;
	while (character(str[data->i]) == 1)
	{
		word[m] = str[data->i];
		(data->i)++;
		m++;
	}
	word[m] = 0;
	if (searchlist(data->env_sorted, word) != NULL)
	{
		current = searchlist(data->env_sorted, word);
		word = current->value;
		m = 0;
		while (word[m] != 0)
		{
			data->lexer_output[data->k][data->j] = word[m];
			m++;
			data->j += 1;
		}
		data->lexer_output[data->k][data->j] = 0;
	}


	if (str[data->i] == ' ')
	{
		data->lexer_output[data->k][data->j] = ' ';
		data->j += 1;
		fsm_space(str, data);
	}
	else if (character(str[data->i]) == 1)
		fsm_character(str, data);
	else if (str[data->i] == '|')
	{
		if (data->k != 0)
			data->k += 1;
		data->j = 0;
		fsm_pipe(str, data);
	}
	else if (str[data->i] == '>')
	{
		if (data->k != 0)
			data->k += 1;
		data->j = 0;
		fsm_greater(str, data);
	}
	else if (str[data->i] == '<')
	{
		if (data->k != 0)
			data->k += 1;
		data->j = 0;
		fsm_smaller(str, data);
	}
	else if (str[data->i] == '$')
		fsm_dollar(str, data);
	else if (str[data->i] == '\"')
		fsm_double_quotes(str, data);
	else if (str[data->i] == '\'')
		fsm_single_quotes(str, data);
	else if (str[data->i] == '\\')
		fsm_backslash(str, data);
	else if (str[data->i] == ';')
		fsm_semicolon(str, data);
	else if (str[data->i] == '\0')
		return ;
	return ;
}
