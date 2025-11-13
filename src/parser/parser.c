/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2025/11/13 19:22:12 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_pipe_position(t_lexer *start)
{
    int cnt = 0;
    while (start && start->token != PIPE)
    {
        cnt++;
        start = start->next;
    }
    return(cnt);
}
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start)
{
    int pos;
    int i;
    
    pos = get_pipe_position(start);
    printf("%d\n", pos);
    i = 0;
    cmd->str = malloc(sizeof(char *) * (pos + 1));
    if(pos>0)
    {
        while (i < pos)
        {
            cmd->str[i] = ft_strdup(start->str);          
            start = start->next;
            i++;
        } 
    }
    if (start && start->token == PIPE)
        return (start->next);
    return (start); 
}
