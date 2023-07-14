/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/07 19:13:36 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_data *data)
{
	char	*pathdirectory;
	
	if (data->split[1] == NULL)
	{
		printf("too few arguments\n");
	}
	else if (data->split[2] == NULL)
	{
		chdir(data->split[1]);
	}
	else
	{
		printf("too many arguments\n");
	}
}
