/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_pipe_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:25:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/02 17:54:29 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_build_in(t_data *data)
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

static void	execution_helper(t_data *data)
{
	DIR		*dir;

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
		perror("");
		exit (126);
	}
	else
		execve(data->split[0], data->split, data->envp);
}

void	execution(t_data *data)
{
	char	*path;

	path = find_path(data->split[0], data->envp);
	if (path == NULL)
		execution_helper(data);
	else
		execve(path, data->split, data->envp);
	exit (127);
}
