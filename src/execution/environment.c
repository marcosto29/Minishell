/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:01 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/14 18:08:12 by matoledo         ###   ########.fr       */
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
		(*env)[i]->key = ft_calloc(sizeof(char),
				ft_size(splitted_arg[0], sizeof(char)) + 1);
		(*env)[i]->value = ft_calloc(sizeof(char),
				ft_size(splitted_arg[1], sizeof(char)) + 1);
		(*env)[i]->key = splitted_arg[0];
		(*env)[i]->value = splitted_arg[1];
		(*env)[i]->exported = 1;
		i++;
	}
}

t_dictionary	**environment(char *operation,
	char **env_arg, t_dictionary **dict_env)
{
	static t_dictionary	**env;

	if (!env)
	{
		initialize_env(&env, env_arg);
		return (NULL);
	}
	if (start_with(operation, "get") == 0)
		return (env);
	if (start_with(operation, "set") == 0)
		env = dict_env;
	return (NULL);
}

//find the value of str key on a dictionary and change it if required
char	*find_key(char *str, char *new_value)
{
	t_dictionary	**env;
	int				i;

	i = 0;
	env = environment("get", NULL, NULL);
	while (env[i])
	{
		if (start_with((char *)env[i]->key, str) == 0)
		{
			if (!new_value)
				return ((char *)env[i]->value);
			free(env[i]->value);
			env[i]->value = ft_strdup(new_value);
			return NULL;
		}
		i++;
	}
	//te lo pongo así de momento para que sea más visual de ver que no se ha encontrado la key
	return (printf("%s key not found\n", str), NULL);
}

char	**dict_to_list(t_dictionary **dict)
{
	char			**list;
	int				counter;

	counter = 0;
	list = ft_calloc(sizeof(char *), ft_dict_size(dict));
	while (dict[counter])
	{
		list[counter] = ft_calloc(sizeof(char), ft_size(dict[counter]->key,
					sizeof(char)) + ft_size(dict[counter]->value,
					sizeof(char)) + 2);
		list[counter] = ft_strjoin(ft_strdup((char *)dict[counter]->key), "=");
		if (dict[counter]->value)
			list[counter] = ft_strjoin(list[counter],
					ft_strdup((char *)dict[counter]->value));
		else
			list[counter] = ft_strjoin(list[counter], ft_strdup(""));
		counter++;
	}
	return (list);
}
