/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:22:35 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/07 16:06:12 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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