/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:00:04 by aosset-o          #+#    #+#             */
/*   Updated: 2025/06/24 15:17:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *str)
{
	char	**split;
	int		len;
	double	res;

	if (ft_strlen(str) == 1 || (ft_strlen(str) == 2 && str[0] == '-'))
		return (ft_atoi(str));
	split = ft_split(str, '.');
	len = ft_strlen(split[1]);
	res = 1;
	while (len > 0)
	{
		res = res * 10;
		len--;
	}
	if (split[0][0] == '-')
		res = ft_atoi(split[0]) - ft_atoi(split[1]) / res;
	else
		res = ft_atoi(split[0]) + ft_atoi(split[1]) / res;
	return (res);
}
