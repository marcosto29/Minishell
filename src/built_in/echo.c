/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:06:11 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/09 21:08:02 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	eol_checker(char *arg)
{
	if (start_with(arg, "-n") != 0)
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
	int	eol;
	int	counter;
	int	args_size;

	args_size = (int)ft_size_dc(args);
	eol = 0;
	counter = 1;
	if (args)
	{
		while (eol_checker(args[counter]) == 0)
			counter++;
		if (counter > 1)
			eol = 1;
		while(args[counter])
		{
			printf("%s", args[counter]);
			if(counter < args_size - 1)
				printf(" ");
			counter++;
		}
	}
	if (eol == 0)
		printf("\n");
}
