/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:06:11 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/28 15:02:04 by matoledo         ###   ########.fr       */
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

int	echo(char **args)
{
	int	eol;
	int	counter;
	int	args_size;

	args_size = (int)ft_size_dc(args);
	eol = 0;
	counter = 0;
	if (args)
	{
		while (eol_checker(args[counter]) == 0)
			counter++;
		if (counter >= 1)
			eol = 1;
		while (args[counter])
		{
			ft_putstr_fd(args[counter], 1);
			if (counter < args_size - 1)
				ft_putstr_fd(" ", 1);
			counter++;
		}
	}
	if (eol == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
