/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:20:44 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/05 10:20:15 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (i);
}

size_t	count_size_variable(const char *str, size_t *i, int *j)
{
	size_t	len;
	char	*value;
	char	*found;
	char	*exit_code;

	len = 0;
	*j = 0;
	(*i)++;
	while (*i < ft_strlen(str) && str[*i] != '$' && !ft_isspace(str[*i]) && str[*i] != '"')
	{
		(*j)++;
		(*i)++;
	}
	value = ft_substr(str, *i - *j, *j);
	if (ft_strncmp(value, "?", 1) == 0)
	{
		exit_code = ft_itoa(*exit_status("get", NULL));
		len = ft_strlen(exit_code);
		free(exit_code);
	}
	else if ((found = find_key(value)) != NULL)
		len = ft_strlen(found);
	free(value);
	return (len);
}

size_t	calculate_total_len(const char *str)
{
	size_t	total_len;
	size_t	i;
	int		j;

	total_len = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '$')
			total_len += count_size_variable(str, &i, &j);
		else
		{
			total_len++;
			i++;
		}
	}
	return (total_len);
}

