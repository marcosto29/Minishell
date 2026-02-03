/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:32:03 by matoledo          #+#    #+#             */
/*   Updated: 2026/02/03 15:50:59 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strlcopy(char *to_copy, char *copied)
{
	while (*copied)
	{
		*to_copy = *copied;
		to_copy++;
		copied++;
	}
}

char	*ft_strcat(char *string1, char *string2)
{
	char	*total_string;
	size_t	total_size;

	total_size = 0;
	total_size += ft_size(string1, sizeof(char));
	total_size += ft_size(string2, sizeof(char));
	total_string = ft_calloc(sizeof(char), total_size + 1);
	ft_strlcopy(total_string, string1);
	ft_strlcopy(total_string + ft_size(total_string, sizeof(char)), string2);
	return (total_string);
}

int	contains_string(char **string_list, char *string)
{
	int	i;

	i = 0;
	while (string_list[i])
	{
		if (ft_strncmp(string_list[i], string,
				ft_size(string_list[i], sizeof(char)) + 1) == 0)
			return (0);
		i++;
	}
	return (1);
}
