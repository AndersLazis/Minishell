/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:18:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/06 22:50:43 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
We need a Makefile .....  Change to aputiev

gcc -L. libft.a minishell.c init_env_sorted.c init_env_unsorted.c find_path.c builtins.c lexer.c expander.c -o minishell -L /goinfre/mschulme/.brew/opt/readline/lib -I /goinfre/mschulme/.brew/opt/readline/include -lreadline
*/

void	signalhandler(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
	{
		;
	}
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

void check_command(int num_args, char **args, t_data *data)
{
	char	*pathdirectory;
	char	*path;
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
		pwd();
	}
	else if (!strcmp(args[0], "echo"))
	{
		i = 1;
		while (i < num_args)
		{
			printf("%s\n", args[i]);
			i++;
		}
	}
	else if (!strcmp(args[0], "export"))
	{
		ft_export(args[1], data);
	}
	else if (!strcmp(args[0], "unset"))///<----------------------Added 06.07.2023---
	{
		ft_unset(args[1], data);
	}
	else if (!strcmp(args[0], "env"))
	{
		ft_env(data);
	}
	else
	{
		args[num_args] = NULL;
		pid = fork();
		if (pid == 0)
		{
			if (args[0][0] == '.' && args[0][1] == '/')
				execve(args[0], args, data->envp);
			else
			{
				path = find_path(args[0], data->envp);
				execve(path, args, data->envp);
				printf ("minishell: command not found: %s\n", args[0]);
			}
			exit(0);
		}
		else
		{
			waitpid (pid, &status, 0);
		}
	}
}

void	shell_loop(t_data *data)
{
	char	*command_line;
	char	**lexer_output;
	char	*token;
	int		num_args;
	char	**args;
	int		i;


	while (1)
	{
		args = NULL;
		args = malloc(sizeof(char*) * 50);
		signal(SIGINT, signalhandler);
		signal(SIGQUIT, signalhandler);
		command_line = get_input_with_rl();
		
	
		lexer_output = lexer(command_line, lexer_output, data);
		i = 0;
		printf("Lexer-Start\n");
		while (lexer_output[i] != NULL)
			printf("\t %s\n", lexer_output[i++]);
		printf("Lexer-End\n");
		

		if (command_line == NULL)
			exit (0);
		token = strtok(command_line, " \t"); //Is STRTOK allowed?
		num_args = 0;
		while (token != NULL)
		{
			args[num_args] = token;
			num_args++;
			token = strtok(NULL, " \t");
		}
		if (args[0] != NULL)
			check_command(num_args, args, data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (EXIT_FAILURE);
	data->ac = ac;
	data->av = av;
	data->envp = env;
	//print_env(env);
	// printf("===============================\n");
	init_env_unsorted(data, env);
	// print_unsorted_list(data);
	//print_env(env);
	// printf("===============================\n");
	init_env_sorted(data, env);	
	// print_sorted_list(data);
	//print_env(env);
	// printf("===============================\n");
	//ft_env(data);
	
	shell_loop(data);
	return (EXIT_SUCCESS);
}
