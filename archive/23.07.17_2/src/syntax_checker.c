/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:06:13 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/07 18:47:07 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	operator(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (1);
	else
		return (0);
}

void	syntax_checker(t_data *data)
{
	int	i;

	i = 0;
	if ((data->nb_single_quotes % 2 == 1) || (data->nb_double_quotes % 2 == 1))
	{
		printf("Odd number of unclosed single or double quotes");
		data->error = -1;
	}
	while (data->lexer_output[i] != NULL)
	{
		if (data->lexer_output[i +1] == NULL)
			break ;
		if (operator(data->lexer_output[i][0]) == 1 && operator(data->lexer_output[i + 1][0]) == 1)
		{
			printf("syntax error near unexpected token `%c'\n", data->lexer_output[i + 1][0]);
			data->error = -1;
			break ;
		}
		i++;
	}
}
