/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:06:13 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 18:18:47 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redirect(char ch)
{
	if (ch == '>' || ch == '<')
		return (1);
	else
		return (0);
}

static int	op(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (1);
	else
		return (0);
}

void	syntax_check_operator(t_data *data, int i)
{
	if (op(data->lexer_output[i][0]) == 1 && data->lexer_output[i + 1] == NULL)
		print_syntax_error_op_in_end(data);
	else if (redirect(data->lexer_output[i][0]) == 1
			&& redirect(data->lexer_output[i + 1][0]) == 1)
		print_syntax_error_double_redirect_sign(data, i);
	else if (ft_strncmp(data->lexer_output[i], ">>>", 3) == 0)
		print_syntax_error_wrong_redirect_token(data);
	else if (ft_strncmp(data->lexer_output[i], "<<<", 3) == 0)
		print_syntax_error_wrong_redirect_token_rev(data);
	else if (ft_strncmp(data->lexer_output[i], "||", 2) == 0)
		print_syntax_error_double_pipe(data);
	else if (op(data->lexer_output[i][0]) == 1
			&& data->lexer_output[i + 1] == NULL)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		data->exit_code = 258;
		data->error = -1;
	}
}

void	syntax_checker(t_data *data)
{
	int	i;

	i = 0;
	syntax_check_syntax_of_first_element(data);
	while (data->lexer_output[i] != NULL && data->error != -1)
	{
		syntax_check_operator(data, i);
		if (data->lexer_output[i + 1] == NULL )
			break ;
		else
			check_last_element(data, i);
		i++;
	}
}
