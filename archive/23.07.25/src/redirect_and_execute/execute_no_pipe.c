/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 20:40:52 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_build_in(t_data *data)
{
	if (ft_strcmp(data->split[0], "exit") == 0)
		ft_exit(data);
	else if (ft_strcmp(data->split[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->split[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->split[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->split[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->split[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->split[0], "unset") == 0)
		ft_unset(data);
	else
		return (-1);
	return (0);
}

static void	clean_up(t_data *data, bool command)
{
	int	j;

	j = 0;
	close(0);
	close(1);
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
	if (command == true)
	{
		j = 0;
		while (data->split[j] != NULL)
		{
			free(data->split[j]);
			j++;
		}
		free(data->split);
	}
}

static void	execute(t_data *data)
{
	int		status;
	char	*path;
	pid_t	pid;

	if (execute_build_in(data) == 0)
		;
	else
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed");
			exit (0);
		}
		if (pid == 0)
		{
			path = find_path(data->split[0], data->envp);
			if (path == NULL)
				execve(data->split[0], data->split, data->envp);
			else
				execve(path, data->split, data->envp);
			printf("minishell: command not found: %s\n", data->split[0]);
			exit (127);
		}
		if (waitpid(-1, &status, 0) == -1)
		{
			perror("waitpid() failed");
			exit (EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
}

void	execute_no_pipe(t_data *data)
{
	bool	command;

	command = true;
	if (data->lexer_output[0][0] == '>' || data->lexer_output[0][0] == '<')
		command = false;
	else
	{
		data->command = data->lexer_output[0];
		data->split = ft_split_arguments(data->command, data);
	}
	data->index = 0;
	// Add the heredoc code
	redirect_in(data);
	redirect_out(data);
	if (command == true)
		execute(data);
	clean_up(data, command);
}
