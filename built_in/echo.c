/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:06:11 by matoledo          #+#    #+#             */
/*   Updated: 2025/10/26 15:10:24 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	echo(char **arguments)
{
	int	i;
	
	i = 0;
	if (arguments)
	{
		while (start_with(arguments[i], "-n") == 0)
			i++;
		printf("%s", arguments[i]);
	}
	if (i == 0)
		printf("\n");
}
