/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 22:36:52 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_and_pipes(t_data *data)
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

static void	arguments_command(t_data *data)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	while (data->cmd_arr[data->index][i] != NULL)
	{
		if (data->cmd_arr[data->index][i][0] == '>' ||
			data->cmd_arr[data->index][i][0] == '<')
		{
			args = split_args(data->cmd_arr[data->index][i + 1], data);
			free(args[0]);
			j = 1;
			while (args[j] != NULL)
			{
				data->split = add_string(data->split, args[j]);
				free(args[j]);
				j++;
			}
			free(args);
		}
		i++;
	}
}

static void	preprocessing(t_data *data, int i)
{
	data->cmd = true;
	if (data->cmd_arr[i][0][0] == '>' || data->cmd_arr[i][0][0] == '<')
	{
		data->cmd = false;
		data->split = NULL;
	}
	else
		data->split = split_args(data->cmd_arr[i][0], data);
	arguments_command(data);
	data->pid_array[i] = fork();
	if (data->pid_array[i] < 0)
		exit (EXIT_FAILURE);
}

static void	create_pipes(t_data *data, int i)
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

static void	heredoc_exits(t_data *data)
{
	char	*temp;
	char	*filename;
	char	**args;
	int		i;

	i = 0;
	data->m = 0;
	while (next_heredoc(data) == true)
	{
		args = split_args(data->cmd_arr[data->index][data->m], data);
		i = 1;
		while (args[i] != NULL)
			data->split = add_string(data->split, args[i++]);
		data->m += 1;
	}
	filename = ft_itoa(data->index);
	temp = ft_strjoin("tmp/temp", filename);
	free(filename);
	filename = ft_strjoin(temp, ".txt");
	data->heredoc_exists[data->index] = open(filename, O_RDWR, 0644);
	dup2(data->heredoc_exists[data->index], STDIN_FILENO);
	free(filename);
}

static void	execute_cmd(t_data *data)
{
	char	*path;

	path = find_path(data->split[0], data->envp);
	if (path == NULL)
	{
		if (searchlist(data->env_sorted, "PATH") == NULL)
			ft_printf(2, "%s: No such file or directory\n", data->split[0]);
		else if (access(data->split[0], F_OK) == -1)
			ft_printf(2, "%s: command not found\n", data->split[0]);
		else if (access(data->split[0], X_OK) == -1)
			perror("");
		else
			execve(data->split[0], data->split, data->envp);
	}
	else
		execve(path, data->split, data->envp);
		exit (127);
}

void	execute_with_pipes(t_data *data)
{
	int	i;

	heredoc_and_pipes(data);
	data->index = 0;
	i = 0;
	while (i < data->pipe_count + 1)
	{
		preprocessing(data, i);
		if (data->pid_array[i] == 0)
		{
			create_pipes(data, i);
			if (data->heredoc_exists[data->index] == 1)
				heredoc_exits(data);
			redirect_out(data);
			if ((data->cmd == 1 || data->split != NULL) && data->error_open_file == 0)
			{
				if (execute_build_in(data) == 0)
					;
				else
					execute_cmd(data);
			}
			exit (data->exit_code);
		}
		reset_func(data);
		i++;
	}
	cleanup(data);
}
