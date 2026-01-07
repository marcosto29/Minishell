/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 19:40:39 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void str_alloc(t_lexer *start, t_simple_cmds *cmd)
{
    int cnt = 0;
    while (start && start->token != PIPE)
    {
        if (start->str)
            cnt++;
        //lo anterior de is_operator fallaba porque como ya se había transformado el caracter le metíamos el GREAT y la comparativa se hacía mal
        //siempre devolvía 0 y nunca hacía el extra jump, lo dejo así para que cualquier operator que detecte lo salte
        else
            start = start->next;
        start = start->next;
    }
    if (cmd->str)
        free_double(cmd->str);
    cmd->str = ft_calloc((cnt + 1), sizeof(char *));
    if (!cmd->str)
        return ;
    cmd->str[cnt] = NULL;
}

char *redirection(t_lexer *start)
{
    if(start->token == 2)
        return(">");   
    if(start->token == 3)
        return(">>");
    if(start->token == 4)
        return("<");
    if(start->token == 5)
        return("<<");
    return(NULL);
}
void free_parcer(t_simple_cmds *list)
{
	if (list->str)
		free_double(list->str);
    if (list->hd_file_name)
		free_double(list->hd_file_name);
    free(list);
}
void fill_redirections(t_simple_cmds *cmd, t_lexer *start, int *i)
{
    if (!start || !start->next)
        return;
    if (redirection(start) && *i < cmd->num_redirections)
    {
        cmd->hd_file_name[*i] = ft_strjoin(redirection(start), start->next->str);
        (*i)++;
    }
}
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start)
{
    int j;
    int k;
    t_lexer *tmp;
    
    tmp = start;
    str_alloc(tmp, cmd);
    j = 0;
    k = 0;
    while (start && start->token != PIPE)
    {
        if (start->token == 0 && start->str)
        {
            cmd->str[j] = ft_strdup(start->str);
            j++;
        }
        else if (start->token > 1 && start->token <= 5 && start->next)
        {
            fill_redirections(cmd, start, &k);
            start = start->next;
        }
        start = start->next;
    }
    if (start && start->token == PIPE)
        return (start->next);
    return (start); 
}
