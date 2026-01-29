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

static int	syntax_error(char unexpected)
{
	int	status;

	status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(unexpected, 2);
	ft_putendl_fd("'", 2);
	exit_status("set", &status);
	return (-1);
}

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
	if (str[i] == '<' && str[i + 1] && str[i + 2]
		&& is_operator(str[i + 1]) == LESS && is_operator(str[i + 2]) == LESS)
		return (syntax_error('<'));
	if (str[i] == '<' && str[i + 1] && is_operator(str[i + 1]) == GREAT)
		return (syntax_error('<'));
	if (str[i] == '>' && str[i + 1] && str[i + 2]
		&& is_operator(str[i + 1]) == GREAT && is_operator(str[i + 2]) == GREAT)
		return (syntax_error('>'));
	if (str[i] == '>' && str[i + 1] && is_operator(str[i + 1]) == LESS)
		return (syntax_error('<'));
	if (is_operator(str[i]) == GREAT && is_operator(str[i + 1]) == GREAT)
		return (add_node(NULL, lexer, GREAT_GREAT), 2);
	if (is_operator(str[i]) == LESS && is_operator(str[i + 1]) == LESS)
		return (add_node(NULL, lexer, LESS_LESS), 2);
	if (is_operator(str[i]) == GREAT)
		return (add_node(NULL, lexer, GREAT), 1);
	if (is_operator(str[i]) == LESS)
		return (add_node(NULL, lexer, LESS), 1);
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
		if (j < 0)
		{
			free_lexer(list);
			return (NULL);
		}
		i += j;
	}
	return (list);
}
