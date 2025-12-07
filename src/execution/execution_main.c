/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:13:19 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/07 16:12:52 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	
	//Aquí hay que cambiar el execute command para que reciba de argumentos los commandos como tal
	// también hay que implementar la redirección de pipes y generación de hijos
	execute_command(argv[1], args, path);
	free_double(path);
	free_double(args);
}
