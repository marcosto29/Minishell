/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:21:38 by aosset-o          #+#    #+#             */
/*   Updated: 2025/11/12 19:45:58 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input = "ls -l | echo > a";
    t_lexer *list = handle_tokens(input);
    t_lexer *tmp = list;
    
    int i = get_pipe_position(tmp);

    while (tmp)
    {
        printf("token=%d ", tmp->token);
        printf("i=%d ", tmp->i);
        if (tmp->str)
            printf(" str=\"%s\"", tmp->str);
        printf("\n");
        tmp = tmp->next;
    }
    /*tmp = list;
    t_simple_cmds *list_2 = parser(tmp);
    t_simple_cmds *tmp_2 = list_2;*/
    tmp = list;
    while (tmp->i < i)
    {
        //tmp_2->str[tmp->i] = tmp->str;
        printf("%d\n", tmp->i);
        tmp = tmp->next;
    }
    free_lexer(list);
    return 0;
}