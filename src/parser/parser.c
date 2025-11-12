/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2025/11/12 19:46:50 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_pipe_position(t_lexer *list)
{
    while (list)
    {
        if(list->token == 1)
            return(list->i);
        list = list->next;
    }
    return(0); 
}
void handle_pipes(t_simple_cmds *commands, t_lexer *lexer)
{
    int i;

    i = get_pipe_position(lexer);
    while (lexer->i < i)
    {
        commands->str[lexer->i] = lexer->str;
        lexer = lexer->next;
    }
    
}
t_simple_cmds *parser(t_lexer *lexer)
{
    t_simple_cmds *list;

    list = malloc(sizeof(t_simple_cmds));
    if(!list)
        return(0);
    handle_pipes(list, lexer);
    return(list);
}

