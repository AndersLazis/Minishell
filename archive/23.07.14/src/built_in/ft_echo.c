/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/13 18:11:01 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_data	*data)
{
	int flag_new_line;
	int	fd;
	int	i;
	int	j;

	fd = 1;
	j = 1;
	flag_new_line = 1;	

	while(data->split[j][0] == '-' && data->split[j][1] == 'n')
	{
		if(data->split[j][2] == '\0')
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
			if (data->split[j][i] == '\'')
			{
				i++;
				while (data->split[j][i] != 0 && data->split[j][i] != '\'')
				{
					ft_putchar_fd(data->split[j][i], fd);
					i++;
				}
				i++;
			}
			if (data->split[j][i] == '\"')
			{
				i++;
				while (data->split[j][i] != 0 && data->split[j][i] != '\"')
				{
					ft_putchar_fd(data->split[j][i], fd);
					i++;
				}
				i++;
			}
			ft_putchar_fd(data->split[j][i], fd);
			i++;
		}	
		ft_putchar_fd(' ', fd);
		j++;
	}
	if (flag_new_line == 1)
		ft_putchar_fd('\n', fd);
}