/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:51:43 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 21:57:31 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_func(t_data *data)
{
	int	j;

	j = 0;
	if (data->cmd == true)
	{
		while (data->split[j] != NULL)
		{
			free(data->split[j]);
			j++;
		}
		free(data->split);
	}
	data->index += 1;
}

void	cleanup(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i++][1]);
	}
	i = 0;
	while (i < data->pipe_count)
	{
		if (waitpid(data->pid_array[i], NULL, 0) == -1)
			exit (EXIT_FAILURE);
		i++;
	}
	waitpid(data->pid_array[data->pipe_count], &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	i = 0;
	while (i < data->pipe_count + 1)
	{
		if (data->heredoc_exists[i++] > 2)
			close(data->heredoc_exists[i]);
	}
	free(data->heredoc_exists);
}
