/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:39:03 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/31 14:08:43 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char **args)
{
	int				i;

	i = 0;
	while (args[i])
	{
		remove_key_value(args[i]);
		i++;
	}
	return (0);
}
