/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/18 11:55:51 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int old_pwd_update()
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf)) != NULL))
		return (-1);
	printf("current wd%s\n", buf);
	return (0);
}

void	ft_cd(t_data *data)
{
	char	*pathdirectory;

	if (data->split[1] == NULL)
	{
		printf("too few arguments\n");
	}
	else if (data->split[2] == NULL)
	{	
		old_pwd_update();
		chdir(data->split[1]);
	}
	else
	{
		printf("too many arguments\n");
	}
}
 