/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 21:54:41 by aputiev          ###   ########.fr       */
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

static void	execution(t_data *data)
{
	char	*path;
	DIR		*dir;

	path = find_path(data->split[0], data->envp);
	if (path == NULL)
	{
		dir = opendir(data->split[0]);
		if (dir)
		{
			closedir(dir);
			ft_printf(2, "%s: is a directory\n", data->split[0]);
			exit (126);
		}
		else if (searchlist(data->env_sorted, "PATH") == NULL)
			ft_printf(2, "%s: No such file or directory\n", data->split[0]);
		else if (access(data->split[0], F_OK) == -1)
			ft_printf(2, "%s: command not found\n", data->split[0]);
		else if (access(data->split[0], X_OK) == -1)
		{
			// exit (126);
			// perror("");
			ft_printf(2, "%s: Permission denied\n", data->split[0]);							//<-changed 23.07.31
			exit (126);
		}
		else
			execve(data->split[0], data->split, data->envp);
	}
	else
		execve(path, data->split, data->envp);
	exit (127);
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
			free(data->split[j++]);
		free(data->split);
	}
}

static void	execute(t_data *data)
{
	int		status;
	pid_t	pid;

	if (execute_build_in(data) == 0)
		;
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("");
			exit (EXIT_FAILURE);
		}
		if (pid == 0)
			execution(data);
		if (waitpid(pid, &status, 0) == -1)
			exit (EXIT_FAILURE);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		close(data->input);
	}
}

void	execute_no_pipe(t_data *data)
{
	bool	command;

	data->error_open_file = false;
	data->index = 0;
	data->input = 0;
	command = true;
	if (data->lexer_output[0][0] == '>' || data->lexer_output[0][0] == '<')
	{
		command = false;
		data->split = NULL;
	}
	else
		data->split = ft_split_arguments(data->lexer_output[0], data);		
	execute_heredoc(data);
	if (data->heredoc_flag == 1)
	{
		data->input = open("tmp/temp.txt", O_RDWR, 0644);
		dup2(data->input, STDIN_FILENO);
	}
	redirect_in(data);
	if (data->error_open_file == false)
	{
		redirect_out(data);
		if ((command == true || data->split != NULL) && data->error_open_file == false)
			execute(data);
	}
	int h = 0;
	while (data->split[h] != NULL)
	{
		printf("data->split[%d]:%s\n", h, data->split[h]);
		h++;
	}	
	clean_up(data, command);
}
