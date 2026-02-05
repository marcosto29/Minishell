/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/05 18:02:02 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_loop(t_simple_cmds	**cmds)
{
	int				i;
	int				exit_value;
	int				*fd;
	int				com_pipe[2];
	int				fdi;

	fdi = 0;
	i = 0;
	exit_value = 0;
	while (cmds[i] && exit_value != -1)
	{
		if (pipe(com_pipe) == -1)
			perror("pipe");
		fd = communication(cmds, fdi, com_pipe, i);
		if (fd && *cmds[i]->str)
			exit_value = execute_command(cmds[i]->str[0],
					cmds[i]->str, fd[0], fd[1]);
		if (fdi != 0)
			close(fdi);
		fdi = com_pipe[0];
		close(com_pipe[1]);
		free(fd);
		i++;
	}
	return (exit_value);
}
