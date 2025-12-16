/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:01 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/16 21:15:09 by matoledo         ###   ########.fr       */
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
		splitted_arg = split(env_arg[i], '=', 1);
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
			return (NULL);
		}
		i++;
	}
	return (NULL);
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

void	add_key_value(char *key, char *value)
{
	t_dictionary	**env;
	t_dictionary	**aux;
	t_dictionary	*new_key_value;

	if (find_key(key, NULL))
	{
		find_key(key, value);
		return;
	}
	aux = environment("get", NULL, NULL);
	env = (t_dictionary **)ft_realloc_d((void **)aux, ft_dict_size(aux) + 2);
	new_key_value = ft_calloc(sizeof(t_dictionary), 1);
	new_key_value->key = ft_strdup(key);
	new_key_value->value = ft_strdup(value);
	env[ft_dict_size(env)] = new_key_value;
	env[ft_dict_size(env) + 1] = '\0';
	environment("set", NULL, env);
}
