/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:01 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/31 14:33:24 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dictionary	*initialize_env(char **env_arg)
{
	int				i;
	char			**splitted_arg;
	t_dictionary	*new;
	t_dictionary	*previous;
	t_dictionary	*first;

	previous = NULL;
	first = ft_calloc(sizeof(t_dictionary), 1);
	i = 0;
	while (env_arg[i] != NULL)
	{
		splitted_arg = split(env_arg[i], '=', 1);
		new = ft_calloc(sizeof(t_dictionary), 1);
		new->key = ft_strdup(splitted_arg[0]);
		if (splitted_arg[1])
			new->value = ft_strdup(splitted_arg[1]);
		else
			new->value = ft_strdup("");
		new->previous = previous;
		if (previous)
			previous->next = new;
		else
		{
			first->next = new;
			new->previous = first;
		}
		previous = new;
		free_double(splitted_arg);
		i++;
	}
	return (first);
}

t_dictionary	*environment(char *operation,
	char **env_arg)
{
	static t_dictionary	*env;

	if (env_arg)
		env = initialize_env(env_arg);
	if (operation)
		return (env);
	return (NULL);
}

void	show_environment(void)
{
	t_dictionary	*env;

	env = environment("get", NULL);
	while (env)
	{
		if (env->key)
			printf("%s=%s\n", (char *)env->key, (char *)env->value);
		env = env->next;
	}
}

void	modify_key_value(char *key, char *value)
{
	t_dictionary	*env;

	env = environment("get", NULL);
	while (env)
	{
		if (start_with(env->key, key) == 0)
		{
			free(env->value);
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = ft_strdup("");
			return ;
		}
		env = env->next;
	}
}

//Find the value of a Key on the dictionary
char	*find_key(char *str)
{
	t_dictionary	*env;

	env = environment("get", NULL);
	while (env)
	{
		if (start_with((char *)env->key, str) == 0)
			return ((char *)env->value);
		env = env->next;
	}
	return (NULL);
}

void	add_key_value(char *key, char *value)
{
	t_dictionary	*env;
	t_dictionary	*new_key_value;

	if (find_key(key))
	{
		modify_key_value(key, value);
		return ;
	}
	env = environment("get", NULL);
	while (env->next)
		env = env->next;
	new_key_value = ft_calloc(sizeof(t_dictionary), 1);
	new_key_value->key = ft_strdup(key);
	if (value)
		new_key_value->value = ft_strdup(value);
	else
		new_key_value->value = ft_strdup("");
	env->next = new_key_value;
	new_key_value->previous = env;
}

void	remove_key_value(char	*key)
{
	t_dictionary	*env;

	env = environment("get", NULL);
	while (env)
	{
		if (start_with(env->key, key) == 0)
		{
			env->previous->next = env->next;
			if (env->next)
				env->next->previous = env->previous;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		env = env->next;
	}
}

char	**dict_to_list(t_dictionary *dict)
{
	char			**list;
	char			*aux;
	int				counter;

	counter = 0;
	list = ft_calloc(sizeof(char *), ft_dict_size(dict) + 1);
	while (dict)
	{
		if (dict->key)
		{
			aux = ft_strjoin((char *)dict->key, "=");
			if (dict->value)
				list[counter] = ft_strjoin(aux, (char *)dict->value);
			else
				list[counter] = ft_strjoin(aux, "");
			counter++;
			free(aux);
		}
		dict = dict->next;
	}
	return (list);
}

void	free_environment(void)
{
	t_dictionary	*env;
	t_dictionary	*aux;

	env = environment("get", NULL);
	while (env)
	{
		aux = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = aux;
	}
}
