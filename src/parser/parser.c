/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 18:30:13 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_pipe_position(t_lexer *start, t_simple_cmds *cmd)
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
        return (0);
    cmd->str[cnt] = NULL;
    return(cnt);
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
void fill_redirections(t_simple_cmds *cmd, t_lexer *start, int *idx)
{
    if (!start || !start->next)
        return;
    if (redirection(start) && *idx < cmd->num_redirections)
    {
        cmd->hd_file_name[*idx] = ft_strjoin(redirection(start), start->next->str);
        (*idx)++;
    }
    start = start->next;
}
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start)
{
    int pos;
    int i;
    int j;
    int k;
    
    pos = get_pipe_position(start, cmd);
    i = -1;
    j = 0;
    k = 0;
    if(pos > 0)
    {
        while ((i++ < pos) && start)
        {
            if (start->token == 0 && start->str)
            {
                cmd->str[j] = ft_strdup(start->str);
                j++;
            }
            else if (start->next && redirection(start))
                fill_redirections(cmd, start, &k);
            start = start->next;
        }
    }
    if (start && start->token == PIPE)
        return (start->next);
    return (start); 
}
