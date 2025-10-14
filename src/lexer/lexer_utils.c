/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:24:50 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 18:24:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isspace(char c)
{
	if(c == 32 || (c>= 9 && c<=14))
		return(-1);
	return(1);
}
int skip_spaces(char *str, int i)
{
	int j;
	j = 0;
	while (ft_isspace(str[i + j]) == 1)
		j++;
	return(j);
}

t_tokens is_operator(char s)
{
	static char token_arr[] = {
		{'|', PIPE},
		{'>', GREAT},
		{'<', LESS},
	};
	if(s == token_arr[0])
		return(token_arr[0]);
	if(s == token_arr[1])
		return(token_arr[1]);
	if(s == token_arr[2])
		return(token_arr[2]);
	return(0);	
}
t_lexer *new_lexer(char *str, char token)
{
	t_lexer *new_element;
	static int i;

	i = 0;
	new_element = malloc(sizeof(t_lexer));
	if(!new_element)
		return(0);
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return(new_element);
}

void ft_lexeradd_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer *tmp;

	tmp = (*lexer);
	if((*lexer))
	{
		while (tmp->next !=NULL)
			tmp = tmp->next;
		tmp->next = new;		
	}
	if(!(*lexer))
		(*lexer) = new;
}