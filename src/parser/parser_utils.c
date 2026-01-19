/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:19:51 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/19 19:34:45 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void str_alloc(t_lexer *start, t_simple_cmds *cmd)
{
    int cnt = 0;
    int red_cnt = 0;
    t_lexer *tmp;
    
    tmp = start;
    while (tmp && tmp->token != PIPE)
    {
        if (tmp->token == 0 && tmp->str)
            cnt++;
        else if (tmp->token > 1 && tmp->token <= 5)
            red_cnt++;
        tmp = tmp->next;
    }
    if (cmd->str)
        free_double(cmd->str);
    cmd->str = ft_calloc((cnt + red_cnt + 1), sizeof(char *));
    if (!cmd->str)
        return ;
    cmd->str[cnt + red_cnt] = NULL;
}
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
void redirections_malloc (t_simple_cmds *cmd)
{
    int cnt;
	t_lexer *aux;

	aux = cmd->tokens;
    cnt = 0;
	while (aux)
	{
		if (aux->token > 1 && aux->token <= 5)
			cnt++;
		aux = aux->next;
	}
	cmd->num_redirections = cnt;
	cmd->hd_file_name = ft_calloc((cnt + 1), sizeof(char *));
	if (cmd->hd_file_name)
		cmd->hd_file_name[cnt] = NULL;
}