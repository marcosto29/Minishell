/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/11 13:49:10 by matoledo         ###   ########.fr       */
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
	char			*line_char;

	history = ft_calloc(sizeof(t_node), 1);
	while (1)
	{
		line_char = ft_strjoin(find_key("PWD"), ": ");
		line = readline(line_char);
		add_list_node(history, line);
		cmd_1 = ft_calloc(sizeof(t_simple_cmds), 1);
		if (exec_loop(line, cmd_1) == -1)
		{
			free_parcer(cmd_1);
			free(line_char);
			break ;
		}
		free_parcer(cmd_1);
		free(line_char);
	}
	free_environment();
	free_list(history);
}
