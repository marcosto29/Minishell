/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:52:14 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/20 19:52:14 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "execution_shell.h"
# include "built_in.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h> 

typedef struct node
{
	void			*value;
	struct node		*previous;
	struct node		*next;
}	t_node;

typedef struct s_global
{
	int	in_cmd;
	int	in_heredoc;
	int	heredoc_sigint;
	int	in_readline;
}	t_global;
extern t_global	g_global;

int		count_pipes(char *str);
int		exec_loop(char *str, t_simple_cmds *cmd);
void	init_signals(void);
void	sigquit_handler(int sig);
#endif
