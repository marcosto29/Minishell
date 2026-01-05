/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/05 19:20:43 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline/readline.h"

int	count_pipes(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (str[i] == 124)
			count++;
		i++;
	}
	return (count);
}

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

	while (command->num_redirections > 0)
	{
		communication_flux = ft_calloc(sizeof(int), 2);
		communication_flux[0] = in_pipe(command->hd_file_name, fdi);
		communication_flux[1] = out_pipe(command->hd_file_name, fdo);
		command->num_redirections++;
	}
	return (communication_flux);
}

int	exec_loop(char *str)
{
	int				pipes;
	int				i;
	int				exit_value;
	t_lexer			*list;
	t_lexer			*list_head;
	t_simple_cmds	*cmd_1;
	int				*flux;
	int				fdi;
	int				fdo;

	fdi = 0;
	fdo = 1;
	list = handle_tokens(str);
	list_head = list;
	pipes = count_pipes(str) + 1;
	i = 0;
	cmd_1 = ft_calloc(sizeof(t_simple_cmds), 1);
	while (i < pipes)
	{
		list = fill_cmds(cmd_1, list);
		flux = communication(cmd_1, fdi, fdo);
		exit_value = execute_command(cmd_1->str[0], cmd_1->str,
				flux[0], flux[1]);
		if (exit_value == -1)
		{
			free(flux);
			break ;
		}
		i++;
		free(flux);
	}
	free_lexer(list_head);
	free_parcer(cmd_1);
	return (exit_value);
}

void	add_list_node(t_node *history, void *value)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	node->value = value;
	while (history->next)
		history = history->next;
	history->next = node;
	node->previous = history;
}

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
	static t_node	*history;

	history = ft_calloc(sizeof(t_node), 1);
	while (1)
	{
		line = readline(NULL);
		add_list_node(history, line);
		if (exec_loop(line) == -1)
			break ;
	}
	free_environment();
	free_list(history);
}
