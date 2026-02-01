/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:47:26 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/01 21:59:37 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef struct s_simple_cmds
{
	char	**str;
	int		num_redirections;
	int		num_pipes;
	char	**hd_file_name;
}	t_simple_cmds;

t_lexer	*fill_cmds(t_simple_cmds *cmd, t_lexer *start, int *red_idx, int j);
void	free_parcer(t_simple_cmds **cmds);
void	redirections_malloc(t_simple_cmds *cmd, t_lexer *start);
void	str_alloc(t_lexer *start, t_simple_cmds *cmd);
void	fill_cmds_array(t_lexer *start, t_simple_cmds **cmds, int num_cmds);
int		ft_cmd_size(t_simple_cmds **cmds);
#endif