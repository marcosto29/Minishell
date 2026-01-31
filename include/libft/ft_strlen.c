/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:01:21 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/31 13:47:36 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	if (str == NULL)
		return (0);
	counter = 0;
	while (*str)
	{
		str++;
		counter++;
	}
	return (counter);
}
