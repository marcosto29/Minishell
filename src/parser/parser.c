/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/14 12:31:29 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void str_alloc(t_lexer *start, t_simple_cmds *cmd)
{
    int cnt = 0;
    int red_cnt = 0;
    t_lexer *tmp;
    
    tmp = start;
    while (tmp && tmp->token != PIPE)
    {
        if (tmp->token == 0 && tmp->str)
            cnt++;
        else if (tmp->token > 1 && tmp->token <= 5)
            red_cnt++;
        tmp = tmp->next;
    }
    if (cmd->str)
        free_double(&cmd->str);
    cmd->str = ft_calloc((cnt + red_cnt + 1), sizeof(char *));
    if (!cmd->str)
        return ;
    cmd->str[cnt + red_cnt] = NULL;
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
		free_double(&list->str);
    if (list->hd_file_name)
		free_double(&list->hd_file_name);
    free(list);
}
void fill_redirections(t_simple_cmds *cmd, t_lexer *start, int *i)
{
    if (!start || !start->next)
        return;
    if (redirection(start) && *i < cmd->num_redirections)
    {
        if(start->next->str)
            cmd->hd_file_name[*i] = ft_strjoin(redirection(start), start->next->str);
        else
            cmd->str[*i] = ft_strdup(redirection(start));
        (*i)++;
    }
}
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start)
{
    int j;
    int k;
    t_lexer *tmp;
    int red_cnt;
    
    tmp = start;
    str_alloc(tmp, cmd);
    
    // Count redirecciones to offset the index
    red_cnt = 0;
    tmp = start;
    while (tmp && tmp->token != PIPE)
    {
        if (tmp->token > 1 && tmp->token <= 5)
            red_cnt++;
        tmp = tmp->next;
    }
    
    j = red_cnt;  // Comandos empiezan después de las redirecciones
    k = 0;
    while (start && start->token != PIPE)
    {
        if (start->token == 0 && start->str)
        {
            cmd->str[j] = expander(start->str);
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
