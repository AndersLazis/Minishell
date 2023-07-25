/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:38:50 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/18 21:07:22 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_data	*data)	//<-changed_19.07.2023
{
	int flag_new_line;
	int	fd;
	int	i;
	int	j;

	fd = 1;
	j = 1;
	flag_new_line = 1;
	if(!data->split[j])
	{
		write(1, "\n", 1);
		return ;
	}
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
			// if (data->split[j][i] == '\'')
			// {
			// 	i++;
			// 	while (data->split[j][i] != 0 && data->split[j][i] != '\'')
			// 	{
			// 		ft_putchar_fd(data->split[j][i], fd);
			// 		i++;
			// 	}
			// 	i++;
			// }
			// if (data->split[j][i] == '\"')
			// {	printf("double!\n");
			// 	i++;
			// 	while (data->split[j][i] != 0 && data->split[j][i] != '\"')
			// 	{
			// 		ft_putchar_fd(data->split[j][i], fd);
			// 		i++;
			// 	}
			// 	i++;
			// }
			ft_putchar_fd(data->split[j][i], fd);
			i++;
		}	
		if(data->split[j+1] != NULL)
			ft_putchar_fd(' ', fd);
		j++;
	}
	if (flag_new_line == 1)
		ft_putchar_fd('\n', fd);
}
