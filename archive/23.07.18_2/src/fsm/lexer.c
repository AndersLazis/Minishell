/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:12:26 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 18:30:36 by mschulme         ###   ########.fr       */
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
	
	data->lexer_output = malloc(1000 * sizeof(char *));
	if (data->lexer_output == NULL)
	{
		printf("Malloc Error");
		exit (0);
	}
	while (data->i < 1000)
	{
		data->lexer_output[data->i] = ft_calloc(1000, 1);
		if (data->lexer_output[data->i] == NULL)
		{
			printf("Malloc Error");
			exit (0);
		}
		data->i += 1;
	}
}

static int check_for_non_ascii(char *str, t_data * data)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] > 126 || str[i] < 0)
		{
			data->error = -1;
			return (-1);
		}
		i++;
	}
	return (0);
}

void	lexer(char *str, t_data *data)
{
	init_lexer(str, data);
	if (check_for_non_ascii(str, data) == -1)
		return ;
	data->i = 0;
	while (str[data->i] != 0)
	{
		if (space(str[data->i]) == 1)
			fsm_space(str, data);
		else if (character(str[data->i]) == 1)
			fsm_character(str, data);
		else if (str[data->i] == '$')
			fsm_dollar(str, data);
		else if (str[data->i] == '|')
			fsm_pipe(str, data);
		else if (str[data->i] == '>')
			fsm_greater(str, data);
		else if (str[data->i] == '<')
			fsm_smaller(str, data);
		else if (str[data->i] == '\"')
			fsm_double_quotes(str, data);
		else if (str[data->i] == '\'')
			fsm_single_quotes(str, data);
	}
	if (data->k == 0)
		data->lexer_output[1] = NULL;
	if (data->lexer_output[data->k][0] == 0)
		data->lexer_output[data->k] = NULL;
	else
		data->lexer_output[data->k + 1] = NULL;
}
