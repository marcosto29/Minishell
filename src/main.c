/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2025/11/13 19:11:22 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input = "ls -l | echo";
    t_lexer *list = handle_tokens(input);
    t_lexer *tmp = list;
    int i = 0;

    t_simple_cmds *cmd_1 = malloc(sizeof(t_simple_cmds));
    t_simple_cmds *cmd_2 = malloc(sizeof(t_simple_cmds));
    tmp = fill_cmds(cmd_1, tmp);
    while (cmd_1->str[i])
    {
        printf("%s\n", cmd_1->str[i]);
        i++;
    }
    tmp = fill_cmds(cmd_2, tmp);
    i = 0;
    while (cmd_2->str[i])
    {
        printf("%s\n", cmd_2->str[i]);
        i++;
    }
    free_lexer(list);
    return 0;
}