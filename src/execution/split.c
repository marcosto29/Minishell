/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:30:13 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/20 20:30:39 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
