/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:47:26 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 16:49:42 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H
#include "minishell.h"
typedef struct s_simple_cmds
{
	char                    **str;
	int                     num_redirections;
	int						num_pipes;
	char                    **hd_file_name;
	t_lexer                 *tokens;
}	t_simple_cmds;
t_lexer	*fill_cmds(t_simple_cmds *cmd, t_lexer *start);
void	free_parcer(t_simple_cmds *list);
void redirections_malloc (t_simple_cmds *cmd_1);
#endif