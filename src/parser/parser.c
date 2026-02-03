/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/03 11:18:11 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redirection(t_lexer *start)
{
	if (start->token == 2)
		return (">");
	if (start->token == 3)
		return (">>");
	if (start->token == 4)
		return ("<");
	if (start->token == 5)
		return ("<<");
	return (NULL);
}

void	free_parcer(t_simple_cmds **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->str)
			free_double(cmds[i]->str);
		if (cmds[i]->hd_file_name)
		{
			if (cmds[i]->num_redirections > 0)
				free_double(cmds[i]->hd_file_name);
			else
				free(cmds[i]->hd_file_name);
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	fill_redirections(t_simple_cmds *cmd, t_lexer *start, int *i)
{
	if (!start || !start->next)
		return ;
	if (redirection(start) && *i < cmd->num_redirections)
	{
		if (start->next->str && start->next->token < 2)
		{
			if (cmd->hd_file_name[*i])
				free(cmd->hd_file_name[*i]);
			cmd->hd_file_name[*i] = ft_strjoin(redirection(start),
					start->next->str);
		}
		else
			cmd->str[*i] = ft_strdup(redirection(start));
		(*i)++;
	}
}

t_lexer	*fill_cmds(t_simple_cmds *cmd, t_lexer *start, int *red_idx, int j)
{
	int		k;
	t_lexer	*tmp;

	tmp = start;
	str_alloc(tmp, cmd);
	k = *red_idx;
	while (start && start->token != PIPE)
	{
		if (start->token == 0 && start->str)
		{
			cmd->str[j] = expander(start->str);
			j++;
		}
		else if (start->token > 1 && start->token <= 5 && start->next)
		{
			fill_redirections(cmd, start, &k);
			start = start->next;
		}
		start = start->next;
	}
	*red_idx = k;
	if (start && start->token == PIPE)
		return (start->next);
	return (start);
}

void	fill_cmds_array(t_lexer *start, t_simple_cmds **cmds, int num_cmds)
{
	int	i;
	int	red_indx;

	i = 0;
	while (i < num_cmds && start)
	{
		cmds[i] = ft_calloc(sizeof(t_simple_cmds), 1);
		red_indx = 0;
		redirections_malloc(cmds[i], start);
		start = fill_cmds(cmds[i], start, &red_indx, 0);
		i++;
	}
}
