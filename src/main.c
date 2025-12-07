/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/07 16:48:11 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int main(int argc, char *argv[], char *env[])
{
    if(!argc || !argv[1])
        return(1);
    t_lexer *list = handle_tokens(argv[1]);
    t_lexer *tmp = list;
    t_dictionary	**aux;
    
    aux = environment(NULL, env, NULL);
    (void)aux;
    //printf("%s\n", find_key("PATH"));
    t_simple_cmds *cmd_1 = malloc(sizeof(t_simple_cmds));
    tmp = fill_cmds(cmd_1, tmp);
    execute_command(cmd_1->str[0],cmd_1->str, env);
    free_lexer(list);
    free_parcer(cmd_1); 
    return 0;
}