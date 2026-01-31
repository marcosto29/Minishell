/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:46 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/31 18:41:07 by aosset-o         ###   ########.fr       */
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

void	free_parcer(t_simple_cmds *cmds, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		if (cmds[i].str)
			free_double(cmds[i].str);
		if (cmds[i].hd_file_name)
		{
			if (cmds[i].num_redirections > 0)
				free_double(cmds[i].hd_file_name);
			else
				free(cmds[i].hd_file_name);
		}
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

// int count_redirections(t_lexer *start)
// {
//     int red_cnt;
//     t_lexer *tmp;

//     tmp = start;
//     red_cnt = 0;
//     while (tmp && tmp->token != PIPE)
//     {
//         if (tmp->token > 1 && tmp->token <= 5)
//             red_cnt++;
//         tmp = tmp->next;
//     }
//     return (red_cnt);
// }

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
void	fill_cmds_array(t_lexer *start, t_simple_cmds *cmds, int num_cmds)
{
	int	i;
	int	red_indx;

	i = 0;
	while (i < num_cmds && start)
	{
		red_indx = 0;
		cmds[i].tokens = start;
		redirections_malloc(&cmds[i], start);
		start = fill_cmds(&cmds[i], start, &red_indx, 0);
		i++;
	}
}
