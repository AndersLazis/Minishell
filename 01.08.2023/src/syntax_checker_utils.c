/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:56:11 by aputiev           #+#    #+#             */
/*   Updated: 2023/08/01 18:01:53 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_syntax_error_op_in_end(t_data *data)
{
	ft_putstr_fd("syntax error near unexpected token `newline' \n", 2);
	data->exit_code = 258;
	data->error = -1;
}

void	print_syntax_error_double_redirect_sign(t_data *data, int i)
{
	ft_printf(2, "syntax error near unexpected token `%s'\n",
		data->lexer_output[i + 1]);
	data->exit_code = 258;
	data->error = -1;
}

void	print_syntax_error_wrong_redirect_token(t_data *data)
{
	ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
	data->exit_code = 258;
	data->error = -1;
}

void	print_syntax_error_wrong_redirect_token_rev(t_data *data)
{
	ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	data->exit_code = 258;
	data->error = -1;
}

void	print_syntax_error_double_pipe(t_data *data)
{
	ft_putstr_fd("Please use only one pipe \n", 2);
	data->exit_code = 42;
	data->error = -1;
}
