/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:50:50 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/31 13:44:32 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
	{
		str = malloc(1 * sizeof(char));
		if (str == NULL)
			return (str);
		str[0] = '\0';
		return (str);
	}
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
