/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:50:50 by aosset-o          #+#    #+#             */
/*   Updated: 2025/12/07 16:28:57 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	if (!n || dest == src)
		return (dest);
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	while (i--)
		((char *)dest)[i] = ((char *)src)[i];
	return (dest);
}
