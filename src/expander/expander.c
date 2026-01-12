/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:20:01 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/12 19:22:57 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expander(char *str)
{
    char *tmp;
    if(dollar_sign(str) != 0 && str[dollar_sign(str) - 2] != '\'' && str[dollar_sign(str)] != '\0')
        printf("HAZ LO TUYO CON EL DOLAR");
    if(str[0] == '\'' && ft_strlen(str) > 2)
        tmp = ft_strtrim(str, "'");
    else if(str[0] == '\"' && ft_strlen(str) > 2)
        tmp = ft_strtrim(str, "\"");
    else 
        tmp = ft_strdup(str);
    return(tmp);
}