/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:42:54 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/25 21:23:10 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	g_flags = 0;

int	tty_get_flag(unsigned int index)
{
	return ((g_flags & (1 << index)) != 0);
}

void	tty_set_flag(unsigned int index, int enable)	//tty_set_flag(TTY_OMIT_LF, 0);
{
	if (enable)
		g_flags |= 1 << index;
	else
		g_flags &= ~(1 << index);
}

void	tty_enter(int is_child)
{
	struct termios	ios;

	tty_set_flag(TTY_IS_CHILD, is_child);
	tcgetattr(STDIN_FILENO, &ios);
	if (is_child)
		ios.c_lflag |= ECHOCTL;
	else
		ios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &ios);
}

static void	signal_handler(int number)
{
	if (number == SIGINT && tty_get_flag(TTY_HEREDOC))
	{
		tty_set_flag(TTY_HEREDOC, 0);
		write(STDERR_FILENO, "\n", 1);
		close(STDIN_FILENO);
		return ;
	}
	if (tty_get_flag(TTY_IS_CHILD))
	{
		if (number == SIGQUIT)
			write(STDERR_FILENO, "Quit\n", 5);
		else
			write(STDERR_FILENO, "\n", 1);
		return ;
	}
	if (number == SIGINT || number == SIGQUIT)
	{
		if (number == SIGINT)
		{
			if (!tty_get_flag(TTY_OMIT_LF))
				write(STDOUT_FILENO, "\n", 1);
			(rl_replace_line("", 1), rl_on_new_line());
		}
		rl_redisplay();
	}
}

void	setup_signal_handling(void)
{
	struct sigaction	action;

	memset(&action, '\0', sizeof(action));
	action.sa_handler = signal_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	tty_enter(0);
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
