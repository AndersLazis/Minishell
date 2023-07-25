/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/09 20:21:02 by aputiev          ###   ########.fr       */
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
		free(current->name);
		free(current->value);
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
		free(current->name);
		free(current->value);
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
