/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:42:54 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/28 20:44:54 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signal)
{	
	if (signal == SIGINT)
	{		
		write(1, "\n", 1);
		if (g_flags == 0)
		{
			rl_replace_line("", 1);
			rl_on_new_line();
		}
		rl_redisplay();
	} 
	if (signal == SIGQUIT)
	{
		if (g_flags == 1)
		{
			printf("Quit: 3\n");
		}
			rl_redisplay();
	}
	
	return ;
}

void	setup_signal_handling(void)
{
	struct sigaction	action;
	
	rl_catch_signals = 0;
	memset(&action, 0, sizeof(struct sigaction));
	sigemptyset(&(action.sa_mask));
	action.sa_handler = signal_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGINT, &action, NULL);
}

/*
void	handle_ctrl_c(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

void	handle_ctrl_backslash(int signum)
{
	rl_redisplay();
	(void)signum;
}

void	setup_signal_handling(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_backslash);
}
*/
