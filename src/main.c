/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/07 11:32:52 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int main(void)
{
	char *input = "echo > patata | wc -l";
    t_lexer *list = handle_tokens(input);
    t_lexer *tmp = list;
    int i = 0;

    t_simple_cmds *cmd_1 = malloc(sizeof(t_simple_cmds));
    t_simple_cmds *cmd_2 = malloc(sizeof(t_simple_cmds));
    tmp = fill_cmds(cmd_1, tmp);
    while (cmd_1->str[i])
    {
        printf("%s\n", cmd_1->str[i]);
        if(cmd_1->hd_file_name)
            printf("%s\n", cmd_1->hd_file_name);
        i++;
    }
    tmp = fill_cmds(cmd_2, tmp);
    i = 0;
    while (cmd_2->str[i])
    {
        printf("%s\n", cmd_2->str[i]);
        //printf("%d\n", i);
        if(cmd_2->hd_file_name)
            printf("%s\n", cmd_2->hd_file_name);
        i++;
    }
    //printf("%d\n", cmd_2->num_redirections);
    free_lexer(list);
    free_parcer(cmd_1);
    free_parcer(cmd_2); 
    return 0;
}