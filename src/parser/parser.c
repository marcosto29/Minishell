/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/20 21:19:41 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void free_parcer(t_simple_cmds *cmd)
{
	if (cmd->str)
		free_double(cmd->str);
    if (cmd->hd_file_name)
		free_double(cmd->hd_file_name);
    free(cmd);
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
// int count_redirections(t_lexer *start)
// {
//     int red_cnt;
//     t_lexer *tmp;

//     tmp = start;
//     red_cnt = 0;
//     while (tmp && tmp->token != PIPE)
//     {
//         if (tmp->token > 1 && tmp->token <= 5)
//             red_cnt++;
//         tmp = tmp->next;
//     }
//     return (red_cnt);
// }

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
