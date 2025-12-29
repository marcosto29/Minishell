/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/29 13:38:45 by aosset-o         ###   ########.fr       */
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

void exec_loop(char *str, t_simple_cmds *cmd_1)
{
    int pipes;
    int i;
    int exit_value;
    t_lexer *list;
    t_lexer *list_head;
    
    list = handle_tokens(str);
    list_head = list;
    pipes = count_pipes(str) + 1;
    i = 0;
    while (i < pipes)
    {
        list = fill_cmds(cmd_1, list);
        // if(ft_strncmp("<<", cmd_1->hd_file_name, 2) == 0)
        // {
        //     printf("AQUI EJECUTA EL HEREDOC\n");
        // }
	    exit_value = execute_command(cmd_1->str[0],cmd_1->str);
        if (exit_value == -1)
            break ;
        i++;
    }
    free_lexer(list_head);
    free_environment();
}
