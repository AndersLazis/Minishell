/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:24:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 00:16:48 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_env_var_char_error(char *split, t_data *data, int print_flag)
{
	if (print_flag == 1)
		ft_printf(2, "export:`%s': not a valid identifier\n", split);
	data->exit_code = 1;
	return (0);
}

int	check_env_var_equal_sign_case(char *split, t_data *data, int print_flag)
{
	if (!ft_strcmp(split, "="))
	{
		if (print_flag == 1)
			ft_printf(2, "export: `%s': not a valid identifier\n", split);
		data->exit_code = 1;
		return (0);
	}
	return (1);
}

int	is_env_var_name_valid(char **split, t_data *data, int print_flag)
{
	int	i;
	int	j;

	j = 1;
	if (!split[1][0] || !split)
		return (0);
	while (split[j] != NULL)
	{
		i = 0;
		if (check_env_var_equal_sign_case(split[j], data, print_flag) == 0)
			return (0);
		while (split[j][i] != '\0' && split[j][i] != '=')
		{
			if (((split[j][0] != '_') && (ft_isalpha(split[j][0]) == 0))
			|| ((split[j][i] != '_') && (ft_isalnum(split[j][i]) == 0)))
			{
				print_env_var_char_error(split[j], data, print_flag);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}
