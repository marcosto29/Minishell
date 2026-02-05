/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/05 19:37:39 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	environment(NULL, env);
	exit_status(NULL, NULL);
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	g_global.heredoc_sigint = 0;
	g_global.in_readline = 0;
	init_signals();
	minishell_loop();
	return (*exit_status("get", NULL));
}
