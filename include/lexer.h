/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:16:03 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 18:16:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H
typedef enum s_tokens
{
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
} t_tokens;
typedef struct s_lexer
{
	char    	*str;
	t_tokens        token;
	int		i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;
int ft_isspace(char c);
int skip_spaces(char *str, int i);
#endif