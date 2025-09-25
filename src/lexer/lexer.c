/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:24:50 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 18:24:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int ft_isspace(char c)
{
	if(c == 32 || (c>= 9 && c<=14))
		return(-1);
	return(1);
}
int skip_spaces(char *str, int i)
{
	int j;
	j = 0;
	while (ft_isspace(str[i +j]) == 1)
		j++;
	return(j);
}
