/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:11:35 by matoledo          #+#    #+#             */
/*   Updated: 2026/02/05 19:56:13 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	own_exit(char **args)
{
	int	i;

	i = 0;
	if (ft_size_dc(args) == 0)
		return (-1);
	while (args[0][i])
	{
		if (ft_isalpha(args[0][i]) == 1)
		{
			exit_status("set", &(int){2});
			return (-1);
		}
		i++;
	}
	if (ft_size_dc(args) > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_status("set", &(int){1});
		return (1);
	}
	exit_status("set", &(int){ft_atoi(args[0])});
	return (-1);
}
