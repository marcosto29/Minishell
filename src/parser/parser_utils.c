/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:19:51 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/03 18:12:20 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_alloc(t_lexer *start, t_simple_cmds *cmd)
{
	int		cnt;
	int		red_cnt;
	t_lexer	*tmp;

	cnt = 0;
	red_cnt = 0;
	tmp = start;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == 0 && tmp->str)
			cnt++;
		tmp = tmp->next;
	}
	if (cmd->str)
		free_double(cmd->str);
	cmd->str = ft_calloc((cnt + 1), sizeof(char *));
	if (!cmd->str)
		return ;
	cmd->str[cnt + red_cnt] = NULL;
}

int	count_commands(char *str)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (str[i] == 124)
			count++;
		i++;
	}
	return (count);
}

void	redirections_malloc(t_simple_cmds *cmd, t_lexer *start)
{
	int		cnt;
	t_lexer	*aux;

	aux = start;
	cnt = 0;
	while (aux && aux->token != PIPE)
	{
		if (aux->token > 1 && aux->token <= 5
			&& aux->next && aux->next->token < 2)
			cnt++;
		aux = aux->next;
	}
	cmd->num_redirections = cnt;
	if (cnt > 0)
		cmd->hd_file_name = ft_calloc((cnt + 1), sizeof(char *));
}

int	ft_cmd_size(t_simple_cmds **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}
