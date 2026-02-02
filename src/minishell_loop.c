/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/01 23:01:03 by matoledo         ###   ########.fr       */
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

// void	minishell_loop(void)
// {
// 	char			*line;
// 	t_simple_cmds	*cmd;
// 	char			*line_char;
// 	int				result;

// 	result = 0;
// 	while (1)
// 	{
// 		line_char = ft_strjoin(find_key("PWD"), ": ");
// 		g_global.in_readline = 1;
// 		line = readline(line_char);
// 		g_global.in_readline = 0;
// 		rl_on_new_line();
// 		if (!line)
// 		{
// 			ft_putendl_fd("exit", 1);
// 			result = -1;
// 		}
// 		else if (*line)
// 		{
// 			add_history(line);
// 			cmd = ft_calloc(sizeof(t_simple_cmds), 1);
// 			result = exec_loop(line, cmd);
// 			free_parcer(cmd);
// 		}
// 		free(line_char);
// 		free(line);
// 		if (result == -1)
// 			break ;
// 	}
// 	free_environment();
// 	free(exit_status("get", NULL));
// 	rl_clear_history();
// }

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

	while (1)
	{
		pwd = ft_strjoin(find_key("PWD"), ": ");
		g_global.in_readline = 1;
		line = readline(pwd);
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
			cmds = build_commands(line);
			result = exec_loop(cmds);
			free_parcer(cmds);
		}
		free(line);
		free(pwd);
		if (result == -1)
			break ;
	}
}
