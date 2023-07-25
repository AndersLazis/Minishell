/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/24 15:24:13 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_unsorted_list(t_data *data)
{
	t_env_list	*current;
	t_env_list	*ptr;
	
	current = data->env_unsorted;
	while(current)
	{
		ptr = current->next;
		//printf("current->name:%s\n", current->name);
		// if(current->name)
			free(current->name);
		// if(current->value)
			free(current->value);
		// if(current)
			free(current);
		current = ptr;
	}
	return(1);
}

int	free_sorted_list(t_data *data)
{
	t_env_list	*current;
	t_env_list	*ptr;
	
	current = data->env_sorted;
	while(current)
	{
		ptr = current->next;
		// if(current->name)
			free(current->name);
		// if(current->value)
			free(current->value);
		// if(current)
			free(current);
		current = ptr;
	}
	return(1);
}

void	ft_exit(t_data *data, int exit_code)	//<-changed_23.07.24
{
	// printf("free_unsorted_list(data):%d\n", free_unsorted_list(data));
	// printf("free_sorted_list(data):%d\n", free_sorted_list(data));
	int	i;
	int j;
	i = 0;
	j = 0;
	
	
	if(free_unsorted_list(data) != 1)
		exit(EXIT_FAILURE);
	if(free_sorted_list(data) != 1)
		exit(EXIT_FAILURE);	
	while(data->lexer_output[i] != NULL)
	{
		free(data->lexer_output[i]);
		i++;
	}
	free(data->lexer_output);
	//free(command_line);

	i = 0;
	while (i < data->pipe_count + 1)	//<-changed_23.07.24
	{	
		while(data->command_array[i][j] != NULL)
		{
			free(data->command_array[i][j]);
			j++;
		}
		free(data->command_array[i]);
		i++;
			
	}		
		// free(data->command_array[i]);
		// i++;
	
	free(data->command_array);

	i = 0;
	while (data->split[i] != NULL)
	{
		free(data->split[i]);
		i++;
	}
	free(data->split);
	free(data);
	i = 0;
	while(data->envp[i]!=NULL)	//<-changed_23.07.24
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);	//<-changed_23.07.24
	printf("Terminating the shell\n");
	exit (exit_code);
	
}
