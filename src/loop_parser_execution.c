/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/13 20:01:11 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *break_w)
{
	int		com_pipe[2];
	char	*line;

	line = NULL;
	if (pipe(com_pipe) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(line, break_w, ft_size(break_w, sizeof(char)) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(com_pipe[1], line, ft_strlen(line));
		write(com_pipe[1], "\n", 1);
		free(line);
	}
	close(com_pipe[1]);
	return (com_pipe[0]);
}

int	in_pipe(char *redirection)
{
	int	fdi;

	if (start_with(redirection, "<<") == 0)
		fdi = heredoc(redirection + 2);
	else
	{
		fdi = open(redirection + 1, O_RDONLY);
		if (fdi == -1)
		{
			perror(redirection + 1);
			return (-1);
		}
	}
	return (fdi);
}

int	out_pipe(char *redirection)
{
	int	fdo;

	if (start_with(redirection, ">>") == 0)
		fdo = open(redirection + 1,
				O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	else
		fdo = open(redirection + 1,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdo == -1)
	{
		perror(redirection + 1);
		return (-1);
	}
	return (fdo);
}

void	handle_redirections(t_simple_cmds *cmd, int *fdi, int *fdo)
{
	int	i;

	i = 0;
	while (cmd->hd_file_name[i])
	{
		if (start_with(cmd->hd_file_name[i], "<") == 0)
		{
			*fdi = in_pipe(cmd->hd_file_name[i]);
			if (*fdi == -1)
				return ;
		}
		else if (start_with(cmd->hd_file_name[i], ">") == 0)
		{
			*fdo = out_pipe(cmd->hd_file_name[i]);
			if (*fdo == -1)
				return ;
		}
		i++;
	}
}

int	*communication(t_simple_cmds *cmd, int fdi, int *pipe, int iter)
{
	int		*communication_flux;
	int		fdo;

	fdo = 1;
	if (cmd->num_pipes - iter > 1)
		fdo = pipe[1];
	handle_redirections(cmd, &fdi, &fdo);
	if (fdi == -1 || fdo == -1)
		return (NULL);
	communication_flux = ft_calloc(sizeof(int), 2);
	if (!communication_flux)
		return (NULL);
	communication_flux[0] = fdi;
	communication_flux[1] = fdo;
	return (communication_flux);
}

int	exec_loop(char *str, t_simple_cmds	*cmd_1)
{
	int				i;
	int				exit_value;
	t_lexer			*list;
	int				*fd;
	int				com_pipe[2];
	int				fdi;

	fdi = 0;
	list = handle_tokens(str);
	i = 0;
	cmd_1->tokens = list;
	redirections_malloc(cmd_1);
	cmd_1->num_pipes = count_pipes(str) + 1;
	exit_value = 0;
	while (i < cmd_1->num_pipes && exit_value != -1)
	{
		if (pipe(com_pipe) == -1)
			perror("pipe");
		list = fill_cmds(cmd_1, list);
		fd = communication(cmd_1, fdi, com_pipe, i);
		if (fd)
			exit_value = execute_command(cmd_1->str[0], cmd_1->str, fd[0], fd[1]);
		if (fdi != 0)
			close(fdi);
		fdi = com_pipe[0];
		close(com_pipe[1]);
		free(fd);
		i++;
	}
	free_lexer(cmd_1->tokens);
	return (exit_value);
}
