/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 15:29:57 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	free_list(t_node *list)
{
	t_node	*aux;

	while (list)
	{
		aux = list->next;
		free(list->value);
		free(list);
		list = aux;
	}
}
void	add_list_node(t_node *history, void *value)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	node->value = value;
	while (history->next)
		history = history->next;
	history->next = node;
	node->previous = history;
}

void	minishell_loop(void)
{
	char			*line;
	t_simple_cmds	*cmd_1;
	static t_node	*history;

	history = ft_calloc(sizeof(t_node), 1);
	while (1)
	{
		line = readline(NULL);
		add_list_node(history, line);
		cmd_1 = ft_calloc(sizeof(t_simple_cmds), 1);
		if (exec_loop(line, cmd_1) == -1)
		{
			free_parcer(cmd_1);
			break ;
		}
		free_parcer(cmd_1);
	}
	free_environment();
	free_list(history);
}