/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:19:51 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 15:32:27 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
int redirections_count (t_simple_cmds *cmd_1)
{
    int cnt;
    cnt = 0;
    while (cmd_1->tokens->token != 1 && cmd_1->tokens)
    {
        if(cmd_1->tokens->token>1 && cmd_1->tokens->token<=5)
            cnt++;
        cmd_1->tokens=cmd_1->tokens->next;
    }
    return(cnt);
}