/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:00:47 by marvin            #+#    #+#             */
/*   Updated: 2025/10/14 12:00:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int add_node(char *str, t_lexer **list, t_tokens token)
{
    t_lexer *node;

    node = new_lexer(list, token);
    if(!node)
        return(0);
    ft_lexeradd_back(list, node);
    return(1);

}
int read_operator(int i, char *str, t_lexer **lexer)
{
    if(is_operator(str[i]) == GREAT && is_operator(str[i + 1]) == GREAT) 
        if(!add_node(NULL,lexer, GREAT_GREAT))
            return(0);
        return(2);
    if(is_operator(str[i]) == LESS && is_operator(str[i + 1]) == LESS) 
        if(!add_node(NULL,lexer, LESS_LESS))
            return(0);
        return(2);
    if(is_operator(str[i]) == GREAT) 
        if(!add_node(NULL,lexer, GREAT))
            return(0);
        return(1);
    if(is_operator(str[i]) == LESS) 
        if(!add_node(NULL,lexer, LESS))
            return(0);
        return(1);
}
int read_word(int i, char *str, t_lexer **lexer)
{
    int j;

    j = 0;
    while (str[i+j])
    {
        if(ft_isspace(str[i+j]) || is_operator(str[i+j]))
            break;
        j++;
    }
    if(!add_node(ft_substr(str, i, j), lexer, 0))
        return(0);
    return(j);     
}
void handle_tokens(char *str)
{
    int i;
    int j;
    t_lexer *list;

    i = 0;
    j = 0;
    list = malloc(sizeof(t_lexer));
    while (str[i])
    {
        j = 0;
        i= skip_spaces(str, j);
        if(is_operator(str[i]))
            j = read_operator(i, str, &list);
        else
            j = read_word(i, str, &list);
        i += j;
    }    
}