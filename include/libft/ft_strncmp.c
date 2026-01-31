/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:53:41 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/31 13:45:46 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	dif;
	int	i;

	i = 0;
	dif = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && n > 0)
	{
		if (s1[i] != s2[i])
		{
			dif = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (dif);
		}
		i++;
		n--;
	}
	return (dif);
}
