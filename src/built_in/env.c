/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:39:03 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/16 19:53:31 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_environment()
{
	t_dictionary	**env;
	int				i;

	env = environment("get", NULL, NULL);
	i = 0;
	while (env[i])
	{
		printf("%s=%s\n", (char *)env[i]->key, (char *)env[i]->value);
		i++;
	}
}

void env(char **args)
{
	char	**splitted_arg;

	if (ft_size_dc(args) == 0)
		show_environment();
	//mientras no encuentre un commando que añada variables en el entorno para ejecutar ese comando
	//luego esta función debería llamar a la ejecución del comando que diga
	if (ft_size_dc(args) == 1 && ft_strchr(args[0], '=') != NULL)
	{
		splitted_arg = split(args[0], '=', 1);		
		add_key_value(splitted_arg[0], splitted_arg[1]);
		show_environment();
		free(splitted_arg);
	}
}