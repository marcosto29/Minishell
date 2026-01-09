#ifndef MINISHELL_H
#define MINISHELL_H
#include "libft/libft.h"
#include "lexer.h"
#include "parser.h"
#include "expander.h"
#include "execution_shell.h"
#include "built_in.h"
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

typedef struct node
{
	void			*value;
	struct node		*previous;
	struct node		*next;
}	t_node;

int	count_pipes(char *str);
int	exec_loop(char *str, t_simple_cmds *cmd_1);
#endif
