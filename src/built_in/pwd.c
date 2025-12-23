/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:35:28 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/23 20:10:26 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Código con función externa que dejan que usemos
// size_t	size;
// char	*directory;

// size = 512;
// directory = getcwd(NULL, size);
// if (directory == NULL)
// 	perror("Error");
// printf("%s\n", directory);
// free(directory);

//función accediendo a la variable de entorno PWD
int	pwd()
{
	printf("%s\n", find_key("PWD"));
	return (0);
}
