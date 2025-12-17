/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:39:03 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/17 20:45:09 by matoledo         ###   ########.fr       */
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
	char			**splitted_arg;
	int				i;

	i = 0;
	if (ft_size_dc(args) == 0)
		show_environment();
	while (args[i] && ft_strchr(args[i], '=') != NULL)
	{
		splitted_arg = split(args[i], '=', 1);		
		add_key_value(splitted_arg[0], splitted_arg[1]);
		free(splitted_arg);
		i++;
	}
	if (args[i])
		execute_command(args[i], args + i);
	else
		show_environment();
}
