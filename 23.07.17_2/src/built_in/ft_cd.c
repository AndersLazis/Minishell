/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 20:28:56 by aputiev          ###   ########.fr       */
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
	{	//old_pwd_update();
		chdir(data->split[1]);
	}
	else
	{
		printf("too many arguments\n");
	}
}

old_pwd_update()
{
	
}