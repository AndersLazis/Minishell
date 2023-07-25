/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:06:13 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 01:16:52 by mschulme         ###   ########.fr       */
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
		ft_putstr_fd("Error: Odd number of unclosed single or double quotes\n", 2);
		data->exit_code = 1;
		data->error = -1;
	}
	else if (data->lexer_output[0] == NULL || data->lexer_output[0][0] == 0)
		data->error = -1;
	else if (data->lexer_output[0][0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		data->exit_code = 258;
		data->error = -1;
	}
	while (data->lexer_output[i] != NULL && data->error != -1)
	{
		if (data->lexer_output[i][0] == '|' && data->lexer_output[i + 1] == NULL)
		{
			ft_putstr_fd("You pipe into the void \n", 2);
			data->exit_code = 1;
			data->error = -1;
		}
		if ((data->lexer_output[i][0] == '<' || data->lexer_output[i][0] == '>') && data->lexer_output[i + 1] == NULL)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			data->exit_code = 258;
			data->error = -1;
		}
		if (data->lexer_output[i][0] == '>' && data->lexer_output[i][1] == '>' && data->lexer_output[i][2] == '>')
		{
			ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
			data->exit_code = 258;
			data->error = -1;
		}
		if (data->lexer_output[i][0] == '<' && data->lexer_output[i][1] == '<' && data->lexer_output[i][2] == '<')
		{
			ft_putstr_fd("syntax error near unexpected token `<<'\n",2);
			data->exit_code = 258;
			data->error = -1;
		}
		if (data->lexer_output[i][0] == '|' && data->lexer_output[i][1] == '|')
		{
			ft_putstr_fd("Please use only one pipe \n", 2);
			data->exit_code = 1;
			data->error = -1;
		}
		if (data->lexer_output[i + 1] == NULL )
			break ;
		if (operator(data->lexer_output[i][0]) == 1 && operator(data->lexer_output[i + 1][0]) == 1 && data->lexer_output[i + 2] == NULL)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			data->exit_code = 258;
			data->error = -1;
		}
		i++;
	}
}
