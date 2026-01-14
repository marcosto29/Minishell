/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:39:57 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/14 12:52:31 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char **args)
{
	char	**splitted_args;
	int		i;

	i = 0;
	if (ft_size_dc(args) == 0)
		show_environment();
	else
	{
		while (args[i])
		{
			if (ft_strchr(args[i], '='))
			{
				splitted_args = split(args[i], '=', 1);
				add_key_value(splitted_args[0], splitted_args[1]);
				free_double(&splitted_args);
			}
			i++;
		}
	}
	return (0);
}
