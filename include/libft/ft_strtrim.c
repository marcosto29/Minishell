/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:32:38 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/05 18:10:51 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*pt_return;
	size_t		memory_size;

	pt_return = s1;
	while (ft_strchr(set, *s1) != NULL)
		s1++;
	while (*pt_return)
		pt_return++;
	while (ft_strchr(set, *pt_return) != NULL)
		pt_return--;
	if (s1 > pt_return)
		return (ft_strdup(""));
	memory_size = pt_return - s1;
	pt_return = ft_calloc(sizeof(char), memory_size + 2);
	if (!pt_return)
		return (NULL);
	ft_memcpy((char *)pt_return, s1, memory_size + 1);
	return ((char *)pt_return);
}
