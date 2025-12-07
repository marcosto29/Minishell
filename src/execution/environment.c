/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:01 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/07 16:08:59 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_env(t_dictionary ***env, char **env_arg)
{
	int		i;
	char	**splitted_arg;

	i = 0;
	while (env_arg[i] != NULL)
		i++;
	*env = ft_calloc(sizeof(t_dictionary *), i + 1);
	i = 0;
	while (env_arg[i] != NULL)
	{
		splitted_arg = split(env_arg[i], '=');
		(*env)[i] = ft_calloc(sizeof(t_dictionary), 1);
		(*env)[i]->key = ft_calloc(sizeof(char), ft_size(splitted_arg[0], sizeof(char)) + 1);
		(*env)[i]->value = ft_calloc(sizeof(char), ft_size(splitted_arg[1], sizeof(char)) + 1);
		(*env)[i]->key = splitted_arg[0];
		(*env)[i]->value = splitted_arg[1];
		i++;
	}
}

t_dictionary	**environment(char *operation, char **env_arg, t_dictionary **dict_env)
{
	static t_dictionary **env;

	if (!env)
	{
		initialize_env(&env, env_arg);
		return (env);
	}
	if (start_with(operation, "get") == 0)
		return (env);
	if (start_with(operation, "set") == 0)
		env = dict_env;
	return (NULL);
}

char *find_key(char *str)
{
	t_dictionary **env;
	int i;
	
	i = 0;
	env = environment("get", NULL, NULL);
	while (env[i])
	{
		if(start_with((char *)env[i]->key, str) == 0)
			return((char *)env[i]->value);
		i++;
	}
	return(ft_putendl_fd("key not found", 2), NULL);	
}