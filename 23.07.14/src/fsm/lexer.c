/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:12:26 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/12 17:22:10 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	character(char ch)
{
	if (ch <= 32 || ch > 126)
		return (0);
	if (ch == '>' || ch == '<')
		return (0);
	if (ch == '$' || ch == '|')
		return (0);
	if (ch == '\'' || ch == '\"')
		return (0);
	if (ch == '\\')
		return (0);
	return (1);
}

int	space(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == ' ')
		return (1);
	else
		return (0);
}

void	init_lexer(char *str, t_data *data)
{
	data->nb_single_quotes = 0;
	data->nb_double_quotes = 0;
	data->pipe_count = 0;
	data->error = 0;
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->lexer_output = malloc((ft_strlen(str) + 1) * sizeof(char *));
	if (data->lexer_output == NULL)
		return ;
	while (data->i < ft_strlen(str) + 1)
	{
		data->lexer_output[data->i] = ft_calloc(ft_strlen(str) + 1000, 1);
		if (data->lexer_output[data->i] == NULL)
			return ;
		data->i += 1;
	}
}

void	lexer(char *str, t_data *data)
{
	init_lexer(str, data);
	data->i = 0;
	if (space(str[0]) == 1)
		fsm_space(str, data);
	else if (character(str[0]) == 1)
		fsm_character(str, data);
	else if (str[0] == '$')
		fsm_dollar(str, data);
	else if (str[0] == '|')
		printf("syntax error near unexpected token `|'");
	else if (str[0] == '>')
		fsm_greater(str, data);
	else if (str[0] == '<')
		fsm_smaller(str, data);
	else if (str[0] == '\"')
		fsm_double_quotes(str, data);
	else if (str[0] == '\'')
		fsm_single_quotes(str, data);
	else if (str[0] == '\\')
		fsm_backslash(str, data);
	else
		data->lexer_output[0] = NULL;
	if (data->k == 0)
		data->lexer_output[1] = NULL;
	else if (data->lexer_output[data->k][0] == 0)
		data->lexer_output[data->k] = NULL;
	else
		data->lexer_output[data->k + 1] = NULL;
}
