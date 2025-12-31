/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_parser_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:28:42 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/31 17:42:01 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline/readline.h"

int count_pipes(char *str)
{
    int count;
    int i;

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
        if(str[i] == 124)
            count++;
        i++;
    }
    return(count);
}

int exec_loop(char *str)
{
    int pipes;
    int i;
    int exit_value;
    t_lexer *list;
    t_lexer *list_head;
    
    list = handle_tokens(str);
    list_head = list;
    pipes = count_pipes(str) + 1;
    i = 0;
    t_simple_cmds *cmd_1 = ft_calloc(sizeof(t_simple_cmds), 1);
    while (i < pipes)
    {
        list = fill_cmds(cmd_1, list);
        // if(ft_strncmp("<<", cmd_1->hd_file_name, 2) == 0)
        // {
        //     printf("AQUI EJECUTA EL HEREDOC\n");
        // }
	    exit_value = execute_command(cmd_1->str[0],cmd_1->str);
        if (exit_value == -1)
            break ;
        i++;
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

void    free_list(t_node *list)
{
    t_node  *aux;

    while (list)
    {
        aux = list->next;
        free(list->value);
        free(list);
        list = aux;
    }
}

void	minishell_loop()
{
	char			*line;
	static t_node	*history;

	history = ft_calloc(sizeof(t_node), 1);
	while (1)
	{
		line = readline(NULL);
		add_list_node(history, line);
		if (exec_loop(line) == -1)
			break;
	}
    free_environment();
    free_list(history);
}
