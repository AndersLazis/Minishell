/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/30 19:51:04 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_process_function(t_data *data, char *split)
{
	if ((searchlist(data->env_sorted, split) == NULL)
		&& (searchlist(data->env_unsorted, split) == NULL))
		data->exit_code = 0;
	else
	{
		if (searchlist(data->env_sorted, split) != NULL)
			remove_env_var_in_sorted(split, data);
		if (searchlist(data->env_unsorted, split) != NULL)
			remove_env_var_in_unsorted(split, data);
	}
	return (0);
}

void	ft_unset(t_data *data)
{
	int		i;

	i = 1;
	if (data->split[1] == NULL)
	{
		data->exit_code = 0;
		return ;
	}
	else
	{
		while (data->split[i] != NULL)
		{
			if (!is_env_var_name_valid(data->split, data, 0))
			{
				printf("unset:`%s': not a valid identifier\n", data->split[1]);
				data->exit_code = 1;
				return ;
			}
			else
				unset_process_function(data, data->split[i]);
			i++;
		}
	}
	update_envp(data);
}

/* frees node */
int	free_list_node(t_env_list	*current)
{
	if (current->name)
		free(current->name);
	if (current->value)
		free(current->value);
	free (current);
	return (0);
}

/* removes environment variable from the unsorted list*/
int	remove_env_var_in_unsorted(char *name, t_data *data)
{
	int			counter;
	t_env_list	*current;
	t_env_list	*previous;

	current = data->env_unsorted;
	counter = 0;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (counter == 0)
				data->env_unsorted = current->next;
			else if (previous && current->next != NULL)
				previous->next = current->next;
			else if (previous && current->next == NULL)
				previous->next = NULL;
			free_list_node(current);
			return (1);
		}
		previous = current;
		current = current->next;
		counter++;
	}
	return (0);
}

/* removes environment variable from the sorted list*/
int	remove_env_var_in_sorted(char *name, t_data *data)
{
	int			counter;
	t_env_list	*current;
	t_env_list	*previous;

	current = data->env_sorted;
	counter = 0;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (counter == 0)
				data->env_sorted = current->next;
			else if (previous && current->next != NULL)
				previous->next = current->next;
			else if (previous && current->next == NULL)
				previous->next = NULL;
			free_list_node(current);
			return (1);
		}
		previous = current;
		current = current->next;
		counter++;
	}
	return (0);
}
