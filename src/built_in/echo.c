/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:06:11 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/07 17:29:31 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int	eol;
	int	counter;

	counter = 1;
	eol = 1;
	if (args)
	{
		eol = start_with(args[1], "-n");
		if (eol == 0)
			counter++;
		while(args[counter])
		{
			printf("%s ", args[counter]);
			counter++;
		}
	}
	if (eol == 1)
		printf("\n");
}
