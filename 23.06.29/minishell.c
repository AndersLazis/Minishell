/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/30 16:14:21 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Install the fix from Discord and then change mschulme to your username

gcc -Wall -Werror -Wextra *.c -o minishell -L /goinfre/aputiev/.brew/opt/readline/lib -I /goinfre/aputiev/.brew/opt/readline/include -lreadline
*/

void	signalhandler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*get_input_with_rl(void)
{
	static char	*line_read;

	if (line_read)
	{
		free (line_read);
		line_read = (char *)NULL;
	}
	line_read = readline (">> ");
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}


void check_command(int num_args, char **args, char **env)
{
	char	*pathdirectory;
	int		status;
	int		pid;
	int		i;

	pathdirectory = NULL;
	if (!strcmp(args[0], "exit"))
	{
		free(args);
		printf("Terminating the shell\n");
		exit (0);
	}
	else if (!strcmp(args[0], "cd"))
	{
		chdir(args[1]);
		printf("%s\n", getcwd(pathdirectory, 42));
	}
	else if (!strcmp(args[0], "pwd"))
	{
		printf("%s\n", getcwd(pathdirectory, 42));
	}
	else if (!strcmp(args[0], "echo"))
	{
		i = 1;				// if the input is in double quotes like echo "test"  it should only printf test and not "test"!
		while (i < num_args)
		{
			printf("%s\n", args[i]);
			i++;
		}
	}
	// if (!strcmp(args[0], "export"))
	// {
	// 	i = 0;
	// 	while (env[i] != NULL)
	// 	{
	// 		printf("%s \n", env[i]);
	// 		i++;
	// 	}
	// }
	else if (!strcmp(args[0], "export")) //<-----ADDED
		{
			ft_export(env);
		}
	else if (!strcmp(args[0], "env"))//<-----ADDED
	{
		ft_env(env);
	}
	else
	{
		args[num_args] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, env);
			printf ("minishell: command not found: %s\n", args[0]);
			exit(0);
		}
		else
		{
			waitpid (pid, &status, 0);
		}
	}
}

void	shell_loop(int ac, char **av, char**env)
{
	char	*command_line;
	char	*token;
	int		num_args;
	char	**args;
	
	(void)ac;
	(void)av;
	args = malloc(sizeof(char*) * 25); 
	while (1)
	{
		signal(SIGINT, signalhandler);
		command_line = get_input_with_rl();
		if (command_line == NULL)
			exit (0);
		token = strtok(command_line, " \t");
		num_args = 0;
		while (token != NULL)
		{
			args[num_args] = token;
			num_args++;
			token = strtok(NULL, " \t");
		}
		check_command(num_args, args, env);
	}
}

int	main(int ac, char **av, char**env)
{
	init_env(env); //<-ADDED TO INITIALIZE ENVIRONMENT
	shell_loop(ac, av, env);
	return (EXIT_SUCCESS);
}
