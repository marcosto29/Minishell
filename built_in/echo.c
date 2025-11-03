/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:06:11 by matoledo          #+#    #+#             */
/*   Updated: 2025/10/29 21:18:58 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	eol_check(char *arg)
{
	if (start_with(arg, "-n") == 1)
		return (1);
	arg += 2;
	while (*arg)
	{
		if (*arg != 'n')
			return (1);
		arg++;
	}
	return (0);
}

void	echo(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (eol_check(args[i]) == 0)
			i++;
		printf("%s", args[i]);
	}
	if (i == 0)
		printf("\n");
}
