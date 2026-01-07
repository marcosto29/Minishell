/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:19:51 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 17:59:43 by aosset-o         ###   ########.fr       */
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
void redirections_malloc (t_simple_cmds *cmd_1)
{
    int cnt;
	t_lexer *aux;

	aux = cmd_1->tokens;
    cnt = 0;
	while (aux)
	{
		if (aux->token > 1 && aux->token <= 5)
			cnt++;
		aux = aux->next;
	}
	cmd_1->num_redirections = cnt;
	cmd_1->hd_file_name = ft_calloc((cnt + 1), sizeof(char *));
	if (cmd_1->hd_file_name)
		cmd_1->hd_file_name[cnt] = NULL;
}