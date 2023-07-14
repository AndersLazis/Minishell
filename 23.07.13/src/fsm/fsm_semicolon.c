/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_semicolon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:16:54 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/07 18:18:24 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fsm_semicolon(char *str, t_data *data)
{
	printf("YOU SHALL NOT PASS! \\ and ; \n");
	data->error = -1;
	return ;
}
