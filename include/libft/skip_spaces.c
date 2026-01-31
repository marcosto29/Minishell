/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:50:38 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/31 13:46:58 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (ft_isspace(str[i + j]) && str[i + j])
		j++;
	return (j);
}
