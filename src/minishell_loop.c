/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/19 22:19:18 by matoledo         ###   ########.fr       */
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
		line = readline(line_char);
		rl_on_new_line();
		if (line && *line)
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
