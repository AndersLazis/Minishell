/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:58:46 by aputiev           #+#    #+#             */
/*   Updated: 2023/08/01 18:13:07 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	syntax_check_syntax_of_first_element(t_data *data)
{
	if ((data->nb_single_quotes % 2 == 1) || (data->nb_double_quotes % 2 == 1))
	{
		ft_putstr_fd("Odd number of unclosed single or double quotes\n", 2);
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
}

void	check_last_element(t_data *data, int i)
{
	if (data->lexer_output[i][0] == '|' && data->lexer_output[i + 1][0] == '|')
	{
		printf("syntax error near unexpected token `%c'\n",
			data->lexer_output[i + 1][0]);
		data->exit_code = 258;
		data->error = -1;
	}
	else if (data->lexer_output[i][0] == '<'
			&& data->lexer_output[i + 1][0] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		data->exit_code = 258;
		data->error = -1;
	}
}
