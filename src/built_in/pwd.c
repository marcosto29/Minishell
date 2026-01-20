/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:35:28 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/19 22:24:45 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//función accediendo a la variable de entorno PWD
int	pwd(void)
{
	printf("%s\n", find_key("PWD"));
	return (0);
}
