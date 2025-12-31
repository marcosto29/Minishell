/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:54:28 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/31 15:09:00 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_string(char **string_list, char *string)
{
	int	i;

	i = 0;
	while (string_list[i])
	{
		if (start_with(string_list[i], string) == 0)
			return (0);
		i++;
	}
	return (1);
}

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

void	*ft_calloc(size_t type, size_t size)
{
	char	*ptr;
	size_t	counter;

	counter = 0;
	ptr = malloc(type * size);
	if (!ptr)
		return (NULL);
	while (counter < type * size)
	{
		ptr[counter] = '\0';
		counter++;
	}
	return ((void *)ptr);
}

void	**ft_realloc_d(void **ptr, size_t new_size)
{
	void	**new_ptr;
	int		i;

	new_ptr = malloc(sizeof(void *) * new_size);
	i = 0;
	while (ptr[i])
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	new_ptr[i] = '\0';
	free(ptr);
	return (new_ptr);
}

int	divides(char *aux, char divider, int amount)
{
	int	divide_number;

	divide_number = 0;
	if (amount > 1)
	{
		while (*aux && *aux != divider)
		{
			divide_number++;
			aux++;
		}
	}
	else
	{
		while (*aux)
		{
			divide_number++;
			aux++;
		}
	}
	return (divide_number);
}

void	string_split(char **splitted, char *to_split, char divider, int amount)
{
	int		divide_number;
	char	*aux;

	while (*to_split && amount != 0)
	{
		divide_number = divides(to_split, divider, amount);
		*splitted = ft_calloc(sizeof(char), divide_number + 1);
		aux = *splitted;
		while (*to_split && divide_number > 0)
		{
			*aux = *to_split;
			aux++;
			to_split++;
			divide_number--;
		}
		splitted++;
		if (*to_split)
			to_split++;
		amount--;
	}
}

char	**split(char *string, char divider, int amount)
{
	int		divide_number;
	char	**splitted_word;
	char	*aux;

	if (!string)
		return (NULL);
	divide_number = 1;
	aux = string;
	while (*aux && amount != 0)
	{
		if (*aux == divider)
		{
			amount--;
			divide_number++;
		}
		aux++;
	}
	splitted_word = ft_calloc(sizeof(char *), divide_number + 1);
	string_split(splitted_word, string, divider, divide_number);
	return (splitted_word);
}

char	*ft_str_new(char *string)
{
	int		size;
	int		i;
	char	*new_string;

	size = ft_size(string, sizeof(char));
	new_string = ft_calloc(sizeof(char), size + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	while (string[i])
	{
		new_string[i] = string[i];
		i++;
	}
	return (new_string);
}

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

	aux = pointer;
	while (*aux)
	{
		free(*aux);
		aux++;
	}
	free(pointer);
	pointer = NULL;
}
