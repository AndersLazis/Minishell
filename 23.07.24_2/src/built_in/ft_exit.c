/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/24 19:26:15 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_unsorted_list(t_data *data)
{
	t_env_list	*current;
	t_env_list	*ptr;
	
	current = data->env_unsorted;
	while (current)
	{
		ptr = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = ptr;
	}
	return (1);
}

int	free_sorted_list(t_data *data)
{
	t_env_list	*current;
	t_env_list	*ptr;
	
	current = data->env_sorted;
	while (current)
	{
		ptr = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = ptr;
	}
	return (1);
}

void    ft_exit(t_data *data)
{
    int exit_code;
    int i;
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
    i = 0;
    while(data->envp[i]!= NULL)
    {
        free(data->envp[i]);
        i++;
    }
    free(data->envp);
    exit_code = data->exit_code;
    free(data);
    printf("Terminating the shell\n");
    exit (exit_code);
}