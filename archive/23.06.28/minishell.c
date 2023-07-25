/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/29 12:29:15 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
gcc -Wall -Werror -Wextra  -lreadline *.c -o minishell
*/

void	shell_loop(int ac, char **av, char **envp)
{
	char	*command;
	char	seps[] = " \t";
	int		num_args;
	char	*args[10];
	char	*part;
	char	*pathdirectory = NULL;
	int		pid;
	int		status;
	
	while (1)
	{
		num_args = 0;
		// command = readline(">> ");
		
		// rl_replace_line();
		// if (strlen(command) > 0)
		// 	add_history(command);

		part = strtok(command, seps);	// Decompose in command and arguments
		while (part != NULL)
		{
			args[num_args] = part;
			num_args++;
			part = strtok(NULL, seps);
		}
		if (!strcmp(args[0], "exit"))
		{
			printf("Terminating the shell\n");
			exit (0);
		}
		if (!strcmp(args[0], "cd"))
		{
			chdir(args[1]);
			printf("%s\n", getcwd(pathdirectory, 42));
		}
		if (!strcmp(args[0], "pwd"))
		{
			printf("%s\n", getcwd(pathdirectory, 2));
			printf("fdf");
			pwd();
		}
		if (!strcmp(args[0], "echo"))
		{
			if (num_args > 0)
				printf("%s\n", args[1]);
		}
		if (!strcmp(args[0], "env"))
		{
			env(envp);
		}
		args[num_args] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execvp(args[0], args);
			printf ("minishell: command not found: %s\n", args[0]);
			exit(0);
		}
		else
		{
			waitpid (pid, &status, 0);
		}
		free(command);
	}
}

int	main(int ac, char **av, char **envp)
{
	shell_loop(ac, av, envp);

	return (EXIT_SUCCESS);
}
