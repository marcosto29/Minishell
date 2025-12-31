/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:47:26 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/30 13:50:58 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H
#include "minishell.h"
typedef struct s_simple_cmds
{
	char                    **str;
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *tokens;
}	t_simple_cmds;
t_lexer	*fill_cmds(t_simple_cmds *cmd, t_lexer *start);
void	free_parcer(t_simple_cmds *list);
#endif