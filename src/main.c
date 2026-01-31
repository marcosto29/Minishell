/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/31 18:44:26 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

// int	main(int argc, char *argv[], char *env[])
// {
// 	(void)argc;
// 	(void)argv;
// 	environment(NULL, env);
// 	g_global.in_cmd = 0;
// 	g_global.in_heredoc = 0;
// 	g_global.heredoc_sigint = 0;
// 	g_global.in_readline = 0;
// 	init_signals();
// 	minishell_loop();
// 	return (0);
// }

int main(int argc, char *argv[])
{
	int				num_cmds;
	t_lexer			*list;
	t_simple_cmds	*cmds;

	if (argc != 2)
		return (1);
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	g_global.heredoc_sigint = 0;
	g_global.in_readline = 0;
	list = handle_tokens(argv[1]);
	if (!list)
		return (1);
	num_cmds = count_pipes(argv[1]) + 1;
	cmds = ft_calloc(num_cmds, sizeof(t_simple_cmds));
	if (!cmds)
	{
		free_lexer(list);
		return (1);
	}
	fill_cmds_array(list, cmds, num_cmds);
	
	// Print debug info
	for (int i = 0; i < num_cmds; i++)
	{
		printf("\n--- Comando %d ---\n", i);
		printf("str:\n");
		if (cmds[i].str)
		{
			for (int j = 0; cmds[i].str[j]; j++)
				printf("  [%d]: %s\n", j, cmds[i].str[j]);
		}
		printf("hd_file_name:\n");
		if (cmds[i].hd_file_name)
		{
			for (int j = 0; cmds[i].hd_file_name[j]; j++)
				printf("  [%d]: %s\n", j, cmds[i].hd_file_name[j]);
		}
	}
	
	free_parcer(cmds, num_cmds);
	free_lexer(list);
	return (0);
}
