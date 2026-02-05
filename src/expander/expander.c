/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:20:01 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/05 18:14:17 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_dollar(char *result, char *value, int k)
{
	char	*tmp;
	char	*exit_code;
	int		j;

	if (ft_strncmp(value, "?", 1) == 0)
	{
		exit_code = ft_itoa(*exit_status("get", NULL));
		j = 0;
		while (exit_code[j])
			result[k++] = exit_code[j++];
		free(exit_code);
		return (j);
	}
	if (!find_key(value))
		return (0);
	tmp = ft_strdup(find_key(value));
	j = 0;
	while (tmp[j])
		result[k++] = tmp[j++];
	free(tmp);
	return (j);
}

static int	process_dollar(char *result, const char *str, size_t *i, int k)
{
	int		j;
	char	*value;

	j = 0;
	(*i)++;
	while (*i < ft_strlen(str) && str[*i] != '$'
		&& !ft_isspace(str[*i]) && str[*i] != '"')
	{
		j++;
		(*i)++;
	}
	value = ft_substr(str, *i - j, j);
	k += handle_dollar(result, value, k);
	free(value);
	return (k);
}

char	*dollar_value(char *str)
{
	char	*result;
	size_t	i;
	int		k;

	result = ft_calloc(calculate_total_len(str) + 1, 1);
	i = 0;
	k = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '$')
			k = process_dollar(result, str, &i, k);
		else
			result[k++] = str[i++];
	}
	return (result);
}

char	*expander(char *str)
{
	char	*tmp;
	int		dollar_pos;

	tmp = NULL;
	dollar_pos = dollar_sign(str);
	if (dollar_pos != 0 && (dollar_pos < 2 || str[dollar_pos - 2] != '\'')
		&& str[dollar_pos] != '\0')
		tmp = dollar_value(str);
	else if (str[0] == '\'' && ft_strlen(str) > 2)
		tmp = ft_strtrim(str, "'");
	else if (str[0] == '\"' && ft_strlen(str) > 2)
		tmp = ft_strtrim(str, "\"");
	else
		tmp = ft_strdup(str);
	return (tmp);
}
