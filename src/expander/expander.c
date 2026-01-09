/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:20:01 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/09 14:55:54 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expander(char *str)
{
    if(dollar_sign(str) != 0 && str[dollar_sign(str) - 2] != '\'' && str[dollar_sign(str)] != '\0')
        printf("HAZ LO TUYO CON EL DOLAR");
    if(str[0] == '\'')
        return(ft_strtrim(str, "\'"));
    if(str[0] == '\"')
        return( ft_strtrim(str, "\""));
    return(ft_strdup(str));
}