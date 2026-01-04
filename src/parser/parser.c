/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/04 15:12:02 by matoledo         ###   ########.fr       */
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
        //lo anterior de is_operator fallaba porque como ya se había transformado el caracter le metíamos el GREAT y la comparativa se hacía mal
        //siempre devolvía 0 y nunca hacía el extra jump, lo dejo así para que cualquier operator que detecte lo salte
        else
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
	int				i;
	if (list->str)
	{
		i = 0;
		while (list->str[i])
		{
            free(list->str[i]);
            i++;
        }
        free(list->str);
    }
    free(list->hd_file_name);
    free(list);
}
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start)
{
    int pos;
    int i;
    int j;
    
    pos = get_pipe_position(start, cmd);
    i = -1;
    j = 0;
    cmd->num_redirections = 0;
    if(pos > 0)
    {
        while ((i++ < pos) && start)
        {
            if (start->token == 0 && start->str)
            {
                //aunque con esto la norminette ya no tire hay que hacer aquí un int j++ a parte del contador que hay en el propio while, 
                //porque si no pasa la siguiente situación ls > hola -l, ls guay lo añade en el 0, i++, salta el operator y el hola, -l guay lo mete pero en el 2 porque antes tmb se ha hecho un salto
                cmd->str[j] = ft_strdup(start->str);
                j++;
            }
            else if(start->next && redirection(start))
            {
                cmd->num_redirections++;
                cmd->hd_file_name = ft_strjoin(redirection(start), start->next->str);
                start = start->next;
            }  
            start = start->next;
        }
    }
    //aquí haciendo ls > hola | env por alguna razón el list no se va al siguiente argumento sino que se queda en el operator >
    //intuyo que será por como he gestionado ahora el bucle con pos
    if (start && start->token == PIPE)
        return (start->next);
    return (start); 
}
