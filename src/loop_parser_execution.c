/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/27 11:40:51 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_loop(char *str, t_simple_cmds	*cmd)
{
	int				i;
	int				exit_value;
	t_lexer			*list;
	int				*fd;
	int				com_pipe[2];
	int				fdi;
	int					red_idx;

	fdi = 0;
	red_idx = 0;
	list = handle_tokens(str);
	i = 0;
	cmd->tokens = list;
	redirections_malloc(cmd);
	cmd->num_pipes = count_pipes(str) + 1;
	exit_value = 0;
	while (i < cmd->num_pipes && exit_value != -1)
	{
		if (pipe(com_pipe) == -1)
			perror("pipe");
		list = fill_cmds(cmd, list, &red_idx);
		fd = communication(cmd, fdi, com_pipe, i);
		if (fd && *cmd->str)
			exit_value = execute_command(cmd->str[0], cmd->str, fd[0], fd[1]);
		if (fdi != 0)
			close(fdi);
		fdi = com_pipe[0];
		close(com_pipe[1]);
		free(fd);
		i++;
	}
	free_lexer(cmd->tokens);
	return (exit_value);
}
