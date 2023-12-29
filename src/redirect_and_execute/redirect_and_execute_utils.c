/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/03 20:17:18 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_and_pipes(t_data *data)
{
	int	i;

	data->error_open_file = false;
	data->input = 0;
	data->heredoc_exists = malloc(sizeof(int) * (data->pipe_count + 1));
	i = 0;
	while (i < data->pipe_count + 1)
		data->heredoc_exists[i++] = 0;
	data->index = 0;
	while (data->index < data->pipe_count + 1)
	{
		heredoc_pipes(data);
		data->index += 1;
	}
	i = 0;
	while (i < data->pipe_count)
	{
		if (pipe(data->pipes[i]) == -1)
			exit (EXIT_FAILURE);
		i++;
	}
}

void	arguments_command(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->cmd_arr[data->index][i] != NULL)
	{
		if (data->cmd_arr[data->index][i][0] == '>' ||
			data->cmd_arr[data->index][i][0] == '<')
		{
			data->args = split_args(data->cmd_arr[data->index][i + 1], data);
			free(data->args[0]);
			j = 1;
			while (data->args[j] != NULL)
			{
				data->temp = add_string(data->split, data->args[j]);
				free(data->split);
				data->split = data->temp;
				free(data->args[j]);
				j++;
			}
			free(data->args);
		}
		i++;
	}
}

void	preprocessing(t_data *data, int i)
{
	data->cmd = true;
	if (data->cmd_arr[i][0][0] == '>' || data->cmd_arr[i][0][0] == '<')
	{
		data->cmd = false;
		data->split = NULL;
	}
	else
	{
		data->split = split_args(data->cmd_arr[i][0], data);
	}
	arguments_command(data);
	data->pid_array[i] = fork();
	if (data->pid_array[i] < 0)
		exit (EXIT_FAILURE);
}

void	create_pipes(t_data *data, int i)
{
	int	j;

	j = 0;
	if (i > 0)
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
	if (i < data->pipe_count)
		dup2(data->pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < data->pipe_count)
	{
		close(data->pipes[j][0]);
		close(data->pipes[j][1]);
		j++;
	}
}
