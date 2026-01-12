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

int	handle_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
	}
	return (j);
}

t_tokens is_operator(char s)
{
	static char token_arr[3][2] = {
		{'|', PIPE},
		{'>', GREAT},
		{'<', LESS},
	};
	if(s == token_arr[0][0])
		return(token_arr[0][1]);
	if(s == token_arr[1][0])
		return(token_arr[1][1]);
	if(s == token_arr[2][0])
		return(token_arr[2][1]);
	return(0);
}
t_lexer *new_lexer(char *str, char token)
{
	t_lexer *new_element;
	static int i;

	new_element = malloc(sizeof(t_lexer));
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

	if (!lexer || !new)
        return;
	tmp = (*lexer);
	if((*lexer))
	{
		while (tmp->next !=NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	if(!(*lexer))
		(*lexer) = new;
}
void free_lexer(t_lexer *list)
{
	t_lexer	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->str);
		free(tmp);
	}
}