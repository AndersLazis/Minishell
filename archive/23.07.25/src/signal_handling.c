/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:42:54 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 20:40:07 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void signal_handler(int signal)
// {
//     write(1, "\n", 1);
//     if (signal == SIGINT)
//     {
//         rl_replace_line("", 1);
//         rl_on_new_line();
//         rl_redisplay();
//     }
//     if (signal == SIGQUIT)
//     {
//         rl_redisplay();
//     }
//     return ;
// }

// void	setup_signal_handling(void)
// {
// 	struct sigaction	action;
	
// 	memset(&action, 0, sizeof(struct sigaction));
// 	sigemptyset(&(action.sa_mask));
// 	action.sa_handler = signal_handler;
// 	action.sa_flags = SA_RESTART;
// 	sigaction(SIGQUIT, &action, NULL);
// 	sigaction(SIGINT, &action, NULL);
// }

///////////////////////////////////////////////////////////////////////

void handle_ctrl_c(int signum)
{   
    // int pid;
    // pid = getpid();
    // printf("pid: %d\n", pid);
    kill(g_pid, SIGKILL);
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)signum;
   
}

void handle_ctrl_backslash(int signum) 
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