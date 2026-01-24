/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:41:19 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/24 11:46:28 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *break_w)
{
	int		com_pipe[2];
	char	*line;

	line = NULL;
	if (pipe(com_pipe) == -1)
		return (perror("pipe"), -1);
	g_global.in_heredoc = 1;
	g_global.heredoc_sigint = 0;
	while (1)
	{
		line = readline(">");
		if (g_global.heredoc_sigint || !line)
			break;
		if (ft_strncmp(line, break_w, ft_size(break_w, sizeof(char)) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, com_pipe[1]);
		free(line);
	}
	g_global.in_heredoc = 0;
	g_global.heredoc_sigint = 0;
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
		fdo = open(redirection + 2,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	int		error;

	fdo = 1;
	if (cmd->num_pipes - iter > 1)
		fdo = pipe[1];
	handle_redirections(cmd, &fdi, &fdo);
	if (fdi == -1 || fdo == -1)
	{
		error = errno;
		exit_status("set", &error);
		return (NULL);
	}
	communication_flux = ft_calloc(sizeof(int), 2);
	if (!communication_flux)
		return (NULL);
	communication_flux[0] = fdi;
	communication_flux[1] = fdo;
	return (communication_flux);
}
