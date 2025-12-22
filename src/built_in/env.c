/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:39:03 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/22 16:29:59 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **args)
{
	if (ft_size_dc(args) > 0)
		printf("env no puede ser ejecutado con argumentos\n");
	show_environment();
	return (0);
}
