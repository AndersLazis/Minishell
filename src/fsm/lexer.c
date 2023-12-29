/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:12:26 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/03 00:39:59 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_for_non_ascii(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] > 126 || str[i] < 0)
		{
			data->error = -1;
			printf("Please, use only ASCII characters as input \n");
			return (-1);
		}
		i++;
	}
	return (0);
}

static void	init_lexer(t_data *data)
{
	data->lexer_output = ft_calloc(sizeof(char *) * 2000, 1);
	if (data->lexer_output == NULL)
		exit (EXIT_FAILURE);
	data->nb_single_quotes = 0;
	data->nb_double_quotes = 0;
	data->pipe_count = 0;
	data->error = 0;
	data->i = 0;
	data->j = 0;
	data->k = 0;
}

static void	lexer_loop(char *str, t_data *data)
{
	if (data->lexer_output[data->k] == NULL)
		data->lexer_output[data->k] = ft_calloc(2500, 1);
	if (data->lexer_output[data->k] == NULL)
		exit (EXIT_FAILURE);
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

void	lexer(char *str, t_data *data)
{
	init_lexer(data);
	if (check_for_non_ascii(str, data) == -1)
		return ;
	while (str[data->i] != 0)
	{
		lexer_loop(str, data);
	}
	if (data->k == 0)
		data->lexer_output[1] = NULL;
	else if (data->lexer_output[data->k][0] == 0)
		data->lexer_output[data->k] = NULL;
}
