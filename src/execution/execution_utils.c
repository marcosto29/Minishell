/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:54:28 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/20 20:32:42 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_size(void *pointer, size_t data_type)
{
	size_t	size;

	size = 0;
	if (!pointer)
		return (size);
	while (*(char *)pointer)
	{
		size++;
		pointer++;
	}
	return (size / data_type);
}

size_t	ft_size_dc(char **double_a)
{
	size_t	size;

	size = 0;
	while (*double_a)
	{
		size++;
		double_a++;
	}
	return (size);
}

size_t	ft_dict_size(t_dictionary *dict)
{
	size_t	size;

	size = 0;
	while (dict)
	{
		dict = dict->next;
		size++;
	}
	return (size);
}

int	start_with(char	*string, char *find)
{
	if (!string || !find)
		return (1);
	while (*find)
	{
		if (*string != *find)
			return (1);
		string++;
		find++;
	}
	return (0);
}

void	free_double(char **pointer)
{
	char	**aux;

	if (!pointer || !*pointer)
		return ;
	aux = pointer;
	while (*aux)
	{
		free(*aux);
		aux++;
	}
	free(pointer);
	pointer = NULL;
}
