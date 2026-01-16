/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/16 16:38:52 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;
int main(int argc, char *argv[], char *env[])
{
	// if(!argc || !argv[1])
	// 	return(1);
	// t_lexer *list = handle_tokens(argv[1]);
	// t_lexer *tmp = list;

	(void)argc;
	(void)argv;
	// t_dictionary	**new_aux;1
	environment(NULL, env);
	// printf("%s\n", find_key("PATH"));
	
	// tmp = fill_cmds(cmd_1, tmp);
	// execute_command(cmd_1->str[0],cmd_1->str, env);
	// t_simple_cmds *cmd_1 = ft_calloc(sizeof(t_simple_cmds), 1);
	// exec_loop(argv[1], cmd_1);	
	// free_parcer(cmd_1);
	// free_environment();
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	init_signals();
	minishell_loop();
    return 0;
}