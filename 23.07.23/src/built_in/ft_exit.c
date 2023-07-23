/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/23 00:29:43 by mschulme         ###   ########.fr       */
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
	
	int	i;
	i = 0;
	while(data->lexer_output[i] != NULL)
	{
		free(data->lexer_output[i]);
		i++;
	}
	free(data->lexer_output);
	//free(command_line);

	i = 0;
	while (i < data->pipe_count + 1)
	{
		free(data->command_array[i]);
		i++;
	}
	free(data->command_array);

	i = 0;
	while (data->split[i] != NULL)
	{
		free(data->split[i]);
		i++;
	}
	free(data->split);
	free(data);
	printf("Terminating the shell\n");
	exit (EXIT_SUCCESS);
}
