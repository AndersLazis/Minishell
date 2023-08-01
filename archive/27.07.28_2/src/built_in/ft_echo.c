/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:38:50 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/24 23:49:24 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_data	*data)
{
	int	flag_new_line;
	int	fd;
	int	i;
	int	j;

	fd = 1;
	j = 1;
	flag_new_line = 1;
	if (!data->split[j])
	{
		write(1, "\n", 1);
		return ;
	}
	j = 1;
	while (data->split[j] != NULL && data->split[j][0] == '-' && data->split[j][1] == 'n')
	{
		if (data->split[j][2] == '\0')
			flag_new_line = 0;
		else
			break ;
		j++;
	}
	while (data->split[j] != NULL)
	{
		i = 0;
		while (data->split[j][i] != '\0')
		{
			ft_putchar_fd(data->split[j][i], fd);
			i++;
		}
		if (data->split[j + 1] != NULL)
			ft_putchar_fd(' ', fd);
		j++;
	}
	if (flag_new_line == 1)
		ft_putchar_fd('\n', fd);
}
