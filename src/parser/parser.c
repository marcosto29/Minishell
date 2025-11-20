/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2025/11/20 17:44:27 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_pipe_position(t_lexer *start)
{
    int cnt = 0;
    while (start && start->token != PIPE)
    {
       if (start->token == 0 && start->str)
            cnt++;
        else if (is_operator(start->token)&& start->next)
            start = start->next;
        start = start->next;
    }
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
	t_simple_cmds	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->str);
        free(tmp->hd_file_name);
		free(tmp);
	}
}
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start)
{
    int pos;
    int i;
    
    pos = get_pipe_position(start);
    i = 0;
    cmd->str = malloc(sizeof(char *) * (pos + 1));
    cmd->num_redirections = 0;
    if(pos>0)
    {
        while (i < pos)
        {
            if (start->token == 0 && start->str)
                cmd->str[i++] = ft_strdup(start->str);
            else if(redirection(start))
            {
                cmd->num_redirections++;
                cmd->hd_file_name = ft_strjoin(redirection(start), start->next->str);
            }     
            start = start->next;
        }
    }
    cmd->str[i] = NULL;
    if (start && start->token == PIPE)
        return (start->next);
    return (start); 
}
