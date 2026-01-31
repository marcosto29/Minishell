/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:31:07 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/31 13:44:47 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*aux;
	size_t			i;

	aux = s;
	i = 0;
	while (i < n)
	{
		aux[i] = c;
		i++;
	}
	return (aux);
}
