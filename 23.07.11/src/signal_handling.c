/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:42:54 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/11 15:35:39 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signal)
{
	write(1, "\n", 1);
	if (signal == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		 
	}
	if (signal == SIGQUIT)
	{	
		printf("abc");
		rl_redisplay();
	}
	return ;
}

#define SIG_IGN         (void (*)(int))1

void	setup_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = signal_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGINT, &action, NULL);
}
