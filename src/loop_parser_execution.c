/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 16:18:05 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *break_word)
{
	int		com_pipe[2];
	char	*line;

	line = NULL;
	if (pipe(com_pipe) == -1)
		perror("pipe");
	while (1)
	{
		line = readline(NULL);
		if (start_with(line, break_word) == 0)
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

int	in_pipe(char *operator, int fdi)
{
	int		in;

	in = fdi;
	if (operator)
	{
		if (start_with(operator, "<<") == 0)
			in = heredoc(operator + 2);
		else if (start_with(operator, "<") == 0)
		{
			in = open(operator + 1, O_RDONLY);
			if (in == -1)
				perror(operator + 1);
		}
	}
	return (in);
}

int	out_pipe(char *operator, int fdo)
{
	int	out;

	out = fdo;
	if (operator)
	{
		if (start_with(operator, ">>") == 0)
			out = open(operator + 1, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (start_with(operator, ">") == 0)
			out = open(operator + 1, O_WRONLY | O_CREAT, 0644);
		if (out == -1)
			perror(operator + 1);
	}
	return (out);
}

int	*communication(t_simple_cmds *command, int fdi, int fdo)
{
	int		*communication_flux;
	if(command->num_redirections == 0)
		communication_flux = ft_calloc(sizeof(int), 2);
	while (command->num_redirections > 0)
	{
		communication_flux = ft_calloc(sizeof(int), 2);
		communication_flux[0] = in_pipe(command->hd_file_name, fdi);
		communication_flux[1] = out_pipe(command->hd_file_name, fdo);
		command->num_redirections--;
	}
	return (communication_flux);
}

int	exec_loop(char *str, t_simple_cmds	*cmd_1)
{
	int				i;
	int				exit_value;
	t_lexer			*list;
	int				*flux;
	int				fd[2];

	fd[0] = 0;
	fd[1] = 1;
	list = handle_tokens(str);
	i = 0;
	cmd_1->tokens = list;
	cmd_1->num_pipes = count_pipes(str) + 1;
	exit_value =0;
	while (i < cmd_1->num_pipes && exit_value != -1)
	{
		list = fill_cmds(cmd_1, list);
		flux = communication(cmd_1, fd[0], fd[1]);
		exit_value = execute_command(cmd_1->str[0], cmd_1->str, flux[0], flux[1]);
		free(flux);
		i++;
	}
	free_lexer(cmd_1->tokens);
	return (exit_value);
}