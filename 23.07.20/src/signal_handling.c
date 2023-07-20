/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:42:54 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/18 17:44:30 by mschulme         ###   ########.fr       */
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
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_redisplay();
	}
	return ;
}

void	setup_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = signal_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGINT, &action, NULL);
}
