/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:39:57 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/14 21:16:35 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(char **args)
{
	(void) args;
	// t_dictionary	*new_env_value;

	// while (*args)
	// {
	// 	if (ft_strchr(*args, '='))
	// 	{

	// 		//añadir la variable a la lista de vairbales de entorno con valor
	// 		//modificar la lista, haciendo un realloc para darle más tamaño y añadirla
	// 	}
	// 	args++;
	// }
	//export marks an environment variable to be exported to child-processes, so that the child inherits them
	//según entiendo sería como añadirla al string doble que vayamos a pasar al execve en la variable de entorno
	//execve(comando, argumentos, entorno) <----- con export se añade al entorno la variable indicada por el usuario
	//se pone un valor al argumento si el usuario lo pone
}