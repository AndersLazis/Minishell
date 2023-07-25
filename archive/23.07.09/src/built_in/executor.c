/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/07 23:31:16 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_data *data)
{
	char	*path;
	int		status;
	int		pid;
	
	pid = fork();
	if (pid == 0)
	{
		path = find_path(data->split[0], data->envp);
		execve(path, data->split, data->envp);
		if (data->split != NULL)
		printf("minishell: command not found: %s\n", data->split[0]);
		exit(0);
	}
	else
		waitpid (pid, &status, 0);
	return ;
}
