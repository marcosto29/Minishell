/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:47:26 by aosset-o          #+#    #+#             */
/*   Updated: 2025/11/13 18:39:59 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H
#include "minishell.h"
typedef enum s_builtins
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
} t_builtins;
typedef struct s_simple_cmds
{
	char                    **str;
	t_builtins              built_ins;
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *tokens;
	struct s_simple_cmds			*next;
	struct s_simple_cmds			*prev;
}	t_simple_cmds;
t_lexer *fill_cmds(t_simple_cmds *cmd, t_lexer *start);
#endif