/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/14 15:26:03 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipes(char *str)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == 34)
        {
            i++;
            while (str[i] != 34)
                i++;            
        }
        if (str[i] == 39)
        {
            i++;
            while (str[i] != 39)
                i++;            
        }
        if(str[i] == 124)
            count++;
        i++;
    }
    return(count);
}

void exec_loop(char *str)
{
    int pipes;
    int i;
    t_lexer *list;
    
    list = handle_tokens(str);
    t_simple_cmds *cmd_1 = malloc(sizeof(t_simple_cmds));
    pipes = count_pipes(str) + 1;
    i = 0;
    while (i < pipes)
    {
        list = fill_cmds(cmd_1, list);
	    execute_command(cmd_1->str[0],cmd_1->str);
        i++;
    }
    free_lexer(list);
	free_parcer(cmd_1);
}
