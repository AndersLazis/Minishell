/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 15:54:56 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_unsorted_list(t_data *data) //<-Added free unsorted list
{
	t_env_list	*current;
	t_env_list	*ptr;
	
	current = data->env_unsorted;
	while(current)
	{
		ptr = current->next;
		//printf("current->name:%s\n", current->name);
		if(current->name)
			free(current->name);
		if(current->value)
			free(current->value);
		if(current)
			free(current);
		current = ptr;
	}
	return(1);
}

int	free_sorted_list(t_data *data) //<-Added free sorted list
{
	t_env_list	*current;
	t_env_list	*ptr;
	
	current = data->env_sorted;
	while(current)
	{
		ptr = current->next;
		if(current->name)
			free(current->name);
		if(current->value)
			free(current->value);
		if(current)
			free(current);
		current = ptr;
	}
	return(1);
}

void	ft_exit(t_data *data)
{
	// free the sorted and unsorted list
	if(free_unsorted_list(data) != 1) //<-Added free unsorted list
		exit(EXIT_FAILURE);
	if(free_sorted_list(data) != 1)	//<-Added free sorted list
		exit(EXIT_FAILURE);
	free(data);
	printf("Terminating the shell\n");
	exit (EXIT_SUCCESS);
}
