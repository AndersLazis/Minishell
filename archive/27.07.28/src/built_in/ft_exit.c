/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/26 22:36:45 by mschulme         ###   ########.fr       */
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

int	is_str_digit(char *str)	//<-changed_23.07.26
{
	int	i;

	i = 0;
	while (str[i])
	{	
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	check_exit_code(char* str)	//<-changed_23.07.26
{
	int	exit_code;
	
	if (!str)
		exit_code = 0;
	else if (!ft_strcmp(str, "-"))
		exit_code = 255;
	else if (is_str_digit(str))
	{
		exit_code = ft_atoi(str);
	}
	else
		exit_code = 255;
	return(exit_code);
}

void	free_data(t_data *data)	//<-changed_23.07.26
{
	int	i;

	i = 0;
	if (free_unsorted_list(data) != 1)
		exit(EXIT_FAILURE);
	if (free_sorted_list(data) != 1)
		exit(EXIT_FAILURE);
	while (data->lexer_output[i] != NULL)
		free(data->lexer_output[i++]);
	free(data->lexer_output);
	//free(command_line);
	i = 0;
	while (i < data->pipe_count + 1)
		free(data->command_array[i++]);
	free(data->command_array);
	i = 0;
	while (data->split[i] != NULL)
		free(data->split[i++]);
	free(data->split);
	i = 0;
	while (data->envp[i] != NULL)
		free(data->envp[i++]);
	free(data->envp);	
}

int	ft_exit(t_data *data)	//<-changed_23.07.26
{
	int	i;

	i = 0;		
	if (data->split[1] && data->split[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if(data->split[1])
		data->exit_code = check_exit_code(data->split[1]);
	printf("data->exit_code:%d\n", data->exit_code);
	free_data(data);	
	i = data->exit_code;
	free(data);
	printf("Terminating the shell\n");
	exit (i);
}
