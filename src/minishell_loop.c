/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/05 16:15:07 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmds	**build_commands(char *line)
{
	t_lexer			*list;
	t_simple_cmds	**cmds;
	int				num_cmds;

	num_cmds = count_commands(line);
	list = handle_tokens(line);
	cmds = ft_calloc(num_cmds + 1, sizeof(t_simple_cmds *));
	fill_cmds_array(list, cmds, num_cmds);
	free_lexer(list);
	return (cmds);
}

void	minishell_loop(void)
{
	char			*line;
	char			*pwd;
	t_simple_cmds	**cmds;
	int				result;

	result = 0;
	while (result != -1)
	{
		pwd = ft_strjoin(find_key("PWD"), ": ");
		g_global.in_readline = 1;
		line = readline(pwd);
		rl_on_new_line();
		g_global.in_readline = 0;
		if (!line)
			result = (ft_putendl_fd("exit", 1), -1);
		else if (*line)
		{
			add_history(line);
			cmds = build_commands(line);
			result = exec_loop(cmds);
			free_parcer(cmds);
		}
		free(line);
		free(pwd);
	}
}
