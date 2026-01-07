/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 19:52:19 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_simple_cmds *cmd_1 = ft_calloc(sizeof(t_simple_cmds), 1);
	exec_loop(argv[1], cmd_1);	
	free_parcer(cmd_1);
	free_environment();
	// minishell_loop();
    return 0;
}