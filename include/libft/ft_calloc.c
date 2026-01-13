/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:30:34 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/13 16:36:11 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
