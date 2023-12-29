/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:17:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/02 00:11:16 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_ctrl_d(t_data *data)
{
	int	i;

	if (free_unsorted_list(data) != 1)
		exit(EXIT_FAILURE);
	if (free_sorted_list(data) != 1)
		exit(EXIT_FAILURE);
	i = 0;
	while (data->envp[i] != NULL)
		free(data->envp[i++]);
	free(data->envp);
	free(data);
	exit(EXIT_FAILURE);
}
