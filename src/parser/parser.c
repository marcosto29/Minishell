/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/29 13:36:09 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_pipe_position(t_lexer *start, t_simple_cmds *cmd)
{
    int cnt = 0;
    while (start && start->token != PIPE)
    {
        if (start->token == 0 && start->str)
            cnt++;
        else if (is_operator(start->token) && start->next)
            start = start->next;
        start = start->next;
    }
    if (cmd->str)
    {
        int j = 0;
        while (cmd->str[j])
        {
            free(cmd->str[j]);
            j++;
        }
        free(cmd->str);
        cmd->str = NULL;
    }
    cmd->str = malloc(sizeof(char *) * (cnt + 1));
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
	t_simple_cmds	*tmp;
	int				i;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->str)
		{
			i = 0;
			while (tmp->str[i])
			{
				free(tmp->str[i]);
				i++;
			}
			free(tmp->str);
		}
		free(tmp->hd_file_name);
		free(tmp);
	}
}
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start)
{
    int pos;
    int i;
    
    pos = get_pipe_position(start, cmd);
    i = -1;
    cmd->num_redirections = 0;
    if(pos > 0)
    {
        while ((i++ < pos) && start)
        {
            if (start->token == 0 && start->str)
                cmd->str[i] = ft_strdup(start->str);
            else if(start->next && redirection(start))
            {
                cmd->num_redirections++;
                cmd->hd_file_name = ft_strjoin(redirection(start), start->next->str);
                start = start->next;
            }  
            start = start->next;
        }
    }
    if (start && start->token == PIPE)
        return (start->next);
    return (start); 
}
