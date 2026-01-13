/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:20:01 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/13 16:48:36 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
size_t malloc_size(char *s)
{
    size_t len;
    size_t i;
    int j;
    char *value;
    
    len = 0;
    i = 0;
    while (i < ft_strlen(s))
    {
        if(s[i] == '$')
        {
            j=0;
            while (s[i++] && s[i] != '$' && !ft_isspace(s[i]) && s[i] != '"')
                j++;
            value = ft_substr(s,i - j, j);
            len += ft_strlen(find_key(value));
            free(value);
        }
        if(s[i] != '$' && i < ft_strlen(s))
        {
            len++;
            i++;
        }
    }
    return(len);
}
int handle_dollar(char *result, char *value)
{
    int i;
    int j;
    char *tmp;
    
    i = 0;
    if(!find_key(value))
        return(0);
    while (result[i] != '\0')
        i++;
    tmp = ft_strdup(find_key(value));
    j = 0;
    while (tmp[j])
    {
        result[i] = tmp[j];
        i++;
        j++;
    }
    free(tmp);
    return(j);    
}
char *dollar_value(char *str)
{
    char *result;
    char *value;
    size_t i;
    int j;
    int k;
    
    result = ft_calloc(malloc_size(str) + 1, 1);
    i = 0;
    k = 0;
    while (i< ft_strlen(str))
    {
        if(str[i] == '$')
        {
            j = 0;
            while (str[i++] && str[i] != '$' && ft_isspace(str[i]) == 0 && str[i] != '"')
                j++;
            value = ft_substr(str,i - j, j);
            k += handle_dollar(result, value);
            free(value);
        }
        if(str[i] != '$' && i< ft_strlen(str))
            result[k++] = str[i++];
    }    
    return(result);   
}
char *expander(char *str)
{
    char *tmp;
    int dollar;
    tmp = str;
    dollar = 0;
    if(dollar_sign(str) != 0 && str[dollar_sign(str) - 2] != '\'' && str[dollar_sign(str)] != '\0')
    {
        dollar = 1;
        tmp = dollar_value(str);        
    }
    if(str[0] == '\'' && ft_strlen(str) > 2)
        tmp = ft_strtrim(tmp, "'");
    else if(str[0] == '\"' && ft_strlen(str) > 2)
        tmp = ft_strtrim(tmp, "\"");
    else if(dollar == 0)
        tmp = ft_strdup(tmp);
    return(tmp);
}