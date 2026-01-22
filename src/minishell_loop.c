/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/22 19:14:03 by aosset-o         ###   ########.fr       */
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

void	minishell_loop(void)
{
	char			*line;
	t_simple_cmds	*cmd;
	char			*line_char;
	int				result;

	result = 0;
	while (1)
	{
		line_char = ft_strjoin(find_key("PWD"), ": ");
		g_global.in_readline = 1;
		line = readline(line_char);
		g_global.in_readline = 0;
		rl_on_new_line();
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			result = -1;
		}
		else if (*line)
		{
			add_history(line);
			cmd = ft_calloc(sizeof(t_simple_cmds), 1);
			result = exec_loop(line, cmd);
			free_parcer(cmd);
		}
		free(line_char);
		free(line);
		if (result == -1)
			break ;
	}
	free_environment();
	free(exit_status("get", NULL));
	rl_clear_history();
}
