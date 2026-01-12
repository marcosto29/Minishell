/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/12 19:38:43 by matoledo         ###   ########.fr       */
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
	t_simple_cmds	*cmd_1;
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
			cmd_1 = ft_calloc(sizeof(t_simple_cmds), 1);
			result = exec_loop(line, cmd_1);
			free_parcer(cmd_1);
		}
		free(line_char);
		free(line);
		if (result == -1)
			break ;
	}
	free_environment();
	rl_clear_history();
}
