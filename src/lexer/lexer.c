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

int	add_node(char *str, t_lexer **list, t_tokens token)
{
	t_lexer	*node;

	node = new_lexer(str, token);
	if (!node)
		return (0);
	ft_lexeradd_back(list, node);
	return (1);
}

int	read_operator(int i, char *str, t_lexer **lexer)
{
	if (is_operator(str[i]) == GREAT && is_operator(str[i + 1]) == GREAT)
	{
		add_node(NULL, lexer, GREAT_GREAT);
		return (2);
	}
	if (is_operator(str[i]) == LESS && is_operator(str[i + 1]) == LESS)
	{
		add_node(NULL, lexer, LESS_LESS);
		return (2);
	}
	if (is_operator(str[i]) == GREAT)
	{
		add_node(NULL, lexer, GREAT);
		return (1);
	}
	if (is_operator(str[i]) == LESS)
	{
		add_node(NULL, lexer, LESS);
		return (1);
	}
	if (is_operator(str[i]) == PIPE)
		return (add_node(NULL, lexer, PIPE), 1);
	return (0);
}

int	read_word(int i, char *str, t_lexer **lexer)
{
	int		j;
	char	*aux;

	j = 0;
	while (str[i + j])
	{
		j += handle_quotes(i + j, str, 34);
		j += handle_quotes(i + j, str, 39);
		if (is_operator(str[i + j]) || ft_isspace(str[i + j]))
			break ;
		j++;
	}
	aux = ft_substr(str, i, j);
	if (j == 0)
	{
		free(aux);
		return (0);
	}
	add_node(aux, lexer, 0);
	return (j);
}

t_lexer	*handle_tokens(char *str)
{
	int		i;
	int		j;
	t_lexer	*list;

	i = 0;
	j = 0;
	list = NULL;
	while (str[i])
	{
		j = 0;
		i += skip_spaces(str, i);
		if (is_operator(str[i]))
			j = read_operator(i, str, &list);
		else
			j = read_word(i, str, &list);
		i += j;
	}
	return (list);
}
