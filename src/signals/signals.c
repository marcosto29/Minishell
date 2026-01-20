/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:58:06 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/20 18:01:03 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int sig)
{
	if(!g_global.in_heredoc)
		write(STDOUT_FILENO, "\n", 1);
	if (g_global.in_heredoc)
	{
		g_global.heredoc_sigint = 1;
		rl_done = 1;
		return ;
	}
	if (g_global.in_readline)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void) sig;
}

void	sigquit_handler(int sig)
{
	write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	signal(sig, SIG_DFL);
	kill(getpid(), SIGQUIT);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}