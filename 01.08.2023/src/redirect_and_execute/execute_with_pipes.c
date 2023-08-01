/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 15:24:12 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cleanup(t_data *data);

static void	heredoc_and_pipes(t_data *data)
{
	int	i;

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
		{
			perror("");
			exit (EXIT_FAILURE);
		}
		i++;
	}
}

static void	arguments_command(t_data *data)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	while (data->command_array[data->index][i] != NULL)
	{
		if (data->command_array[data->index][i][0] == '>' ||
			data->command_array[data->index][i][0] == '<')
		{
			args = split_args(data->command_array[data->index][i + 1], data);
			j = 1;
			while (args[j] != NULL)
			{
				data->split = add_string(data->split, args[j]);
				j++;
			}
		}
		i++;
	}
}

void	execute_with_pipes(t_data *data)
{
	char	**arguments;
	bool	command;
	char	*path;
	int		i;
	int		j;

	heredoc_and_pipes(data);
	data->error_open_file = false;
	data->heredoc_flag = 0;
	data->index = 0;
	data->input = 0;
	i = 0;
	while (i < data->pipe_count + 1)
	{
		command = true;
		if (data->command_array[i][0][0] == '>' || data->command_array[i][0][0] == '<')
		{
			command = false;
			data->split = NULL;
		}
		else
			data->split = split_args(data->command_array[i][0], data);
		arguments_command(data);
		data->pid_array[i] = fork();
		if (data->pid_array[i] < 0)
			exit (EXIT_FAILURE);
		if (data->pid_array[i] == 0)
		{
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
			if (data->heredoc_exists[data->index] == 1)
			{
				char	*filename;

				data->m = 0;
				while (next_heredoc(data) == true)
				{
					arguments = split_args(data->command_array[data->index][data->m], data);
					i = 1;
					while (arguments[i] != NULL)
						data->split = add_string(data->split, arguments[i++]);
					data->m += 1;
				}
				filename = ft_strjoin(ft_strjoin("tmp/temp", ft_itoa(data->index)), ".txt");
				data->heredoc_exists[data->index] = open(filename, O_RDWR, 0644);
				dup2(data->heredoc_exists[data->index], STDIN_FILENO);
			}
			redirect_out(data);
			if ((command == true || data->split != NULL) && data->error_open_file == false)
			{
				if (execute_build_in(data) == 0)
					;
				else
				{
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
			}
			exit (data->exit_code);
		}
		j = 0;
		if (command == true)
		{
			while (data->split[j] != NULL)
			{
				free(data->split[j]);
				j++;
			}
			free(data->split);
		}
		data->index += 1;
		i++;
	}
	cleanup(data);
}

static void	cleanup(t_data *data)
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
}
