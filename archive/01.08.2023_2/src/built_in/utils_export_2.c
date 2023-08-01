/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:14:03 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/30 23:06:15 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fill_name(t_data *data, t_env_list *current, int j)
{
	int	k;

	k = 0;
	while (current->name[k] != '\0')
	{
		data->envp[j][k] = current->name[k];
		k++;
	}
	return (k);
}

int	fill_value(t_data *data, t_env_list *current, int j, int k)
{
	int	m;

	m = 0;
	while (current->value[m] != '\0')
	{
		data->envp[j][k] = current->value[m];
		k++;
		m++;
	}
	return (k);
}

int	fill_new_envp_arr(t_data *data, int i)
{
	t_env_list	*current;
	int			j;
	int			k;
	int			m;

	j = 0;
	current = data->env_unsorted;
	while (i-- && current)
	{
		data->envp[j] = ft_calloc(1, ft_strlen(current->name)
				+ ft_strlen(current->value) + 2);
		if (!data->envp[j])
			return (EXIT_FAILURE);
		k = fill_name(data, current, j);
		data->envp[j][k] = '=';
		k++;
		m = 0;
		if (current->value)
			k = fill_value(data, current, j, k);
		data->envp[j][k] = '\0';
		j++;
		current = current->next;
	}
	data->envp[j] = NULL;
	return (0);
}

int	env_list_len(t_env_list	*current)
{
	int	i;

	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	update_envp(t_data *data)
{
	char		**new_envp;
	t_env_list	*current;
	int			i;

	i = 0;
	while (data->envp && data->envp[i] != NULL)
	{
		free(data->envp[i]);
		i++;
	}
	if (data->envp)
		free(data->envp);
	i = 0;
	current = data->env_unsorted;
	i = env_list_len(current);
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (EXIT_FAILURE);
	new_envp[i] = NULL;
	data->envp = new_envp;
	fill_new_envp_arr(data, i);
	return (0);
}
