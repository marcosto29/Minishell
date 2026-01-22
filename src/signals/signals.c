/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:58:06 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/22 20:31:51 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int sig)
{
	if (!g_global.in_heredoc)
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
	if (g_global.in_heredoc || g_global.in_cmd)
	{
		ft_putstr_fd("Quit (core dumped)", 2);
		if(g_global.in_cmd)
			write(1,"\n",1);
		g_global.heredoc_sigint = 1;
		rl_done = 1;
		return;	
	}
	else
		signal(SIGQUIT, SIG_IGN);
	(void)sig;
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
