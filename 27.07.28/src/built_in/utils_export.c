/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:24:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/24 23:58:08 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_var_name_valid(char **split, t_data *data)
{
	int	i;
	int	j;

	j = 1;
	if (!split[1][0] || !split)
		return (0);
	while (split[j] != NULL)
	{
		i = 0;
		if (!ft_strcmp(split[j], "="))
		{
			printf("export: `%s': not a valid identifier\n", split[j]);
			data->exit_code = 1;
			return (0);
		}
		while (split[j][i] != '\0' && split[j][i] != '=')
		{
			if ((split[j][0] != '_') && (ft_isalpha(split[j][i]) == 0))
			{
				printf("export: `%s': not a valid identifier\n", split[j]);
				data->exit_code = 1;
				return (0);
			}
			if ((split[j][i] != '_') && (ft_isalnum(split[j][i]) == 0))
			{
				printf("export: `%s': not a valid identifier\n", split[j]);
				data->exit_code = 1;
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}
