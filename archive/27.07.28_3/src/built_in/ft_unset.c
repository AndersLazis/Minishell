/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/29 19:12:24 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data)	//<-changed_23.07.29
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
			{	
				if((searchlist(data->env_sorted, data->split[i]) == NULL) && (searchlist(data->env_unsorted, data->split[i]) == NULL))
					data->exit_code = 0;
				else
				{
					if (searchlist(data->env_sorted, data->split[i]) != NULL)
					{
						//deletenode(data->env_sorted, data->split[i]);
						remove_env_var_in_sorted(data->split[i], data);
					}
					if (searchlist(data->env_unsorted, data->split[i]) != NULL)
					{
						//deletenode(data->env_unsorted, data->split[i]);
						remove_env_var_in_unsorted(data->split[i], data);
					}
				}				
			}
			i++;
		}
	}
	update_envp(data);
}

/*========================================REMOVE VARIABLE==============================================*/
/* removes environment variable from the unsorted list*/
int remove_env_var_in_unsorted(char *name, t_data *data)	//<-changed_23.07.29
{
	int	i;
	int counter;
	t_env_list	*current;
	t_env_list *previous;

	current = data->env_unsorted;
	counter = 0;
	while(current)
	{	
		i = 0;
		if(ft_strcmp(current->name, name) == 0)
		{
			if(counter == 0) 						//1st case (var in begin of the link list)
				data->env_unsorted = current->next;
			else if(previous && current->next != NULL) //2nd case (var in middle of the link list)
				previous->next = current->next;
			else if(previous && current->next == NULL) //3rd case (var in the end of the link list)
				previous->next = NULL;
			if(current->name)
				free(current->name);
			if(current->value)
				free(current->value);
			free(current);
			return (1);
		}
		previous=current;
		current=current->next;
		counter++;
	}
	return (0);
}


/* removes environment variable from the sorted list*/
int remove_env_var_in_sorted(char *name, t_data *data)	//<-changed_23.07.29
{
	int	i;
	int counter;
	t_env_list	*current;
	t_env_list *previous;

	current = data->env_sorted;
	counter = 0;
	while(current)
	{	
		i = 0;
		if(ft_strcmp(current->name, name) == 0)
		{
			if(counter == 0) 						//1st case (var in begin of the link list)
				data->env_sorted = current->next;
			else if(previous && current->next != NULL) //2nd case (var in middle of the link list)
				previous->next = current->next;
			else if(previous && current->next == NULL) //3rd case (var in the end of the link list)
				previous->next = NULL;
			if(current->name)
				free(current->name);
			if(current->value)
				free(current->value);
			free(current);
			return (1);
		}
		previous=current;
		current=current->next;
		counter++;
	}
	return (0);
}
