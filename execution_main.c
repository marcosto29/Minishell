/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:13:19 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/07 12:06:00 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_shell.h"

int	main(int argc, char *argv[])
{
	char	**path;
	char	**args;
	t_dictionary	**env;
	int		i;

	env = environment(NULL, argv + argc + 1, NULL);
	printf("%s", (char *)env[0]->key);
	i = argc + 1;
	path = ft_calloc(sizeof(char *), 2);
	args = ft_calloc(sizeof(char *), 2);
	while (argv[i] && start_with(argv[i], "PATH") == 1)
		i++;
	if (!argv[i])
	{
		printf("PATH not found\n");
		return (1);
	}
	path[0] = ft_str_new(argv[i] + 5);
	if (!path[0])
	{
		free(path);
		perror("Error");
		return (1);
	}
	path[1] = NULL;
	//importante pasar esto para que haya buen mensaje de error
	if (argv[2])
	{
		args[0] = ft_str_new(argv[2]);
		args[1] = NULL;
	}
	//Aquí hay que cambiar el execute command para que reciba de argumentos los commandos como tal
	// también hay que implementar la redirección de pipes y generación de hijos
	execute_command(argv[1], args, path);
	free_double(path);
	free_double(args);
}
