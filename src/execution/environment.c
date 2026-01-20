/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:01 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/20 20:37:18 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dictionary	*create_env_node(char *env)
{
	t_dictionary	*new;
	char			**splitted;

	splitted = split(env, '=', 1);
	new = ft_calloc(sizeof(t_dictionary), 1);
	if (!new)
		return (NULL);
	new->key = ft_strdup(splitted[0]);
	if (splitted[1])
		new->value = ft_strdup(splitted[1]);
	else
		new->value = ft_strdup("");
	free_double(splitted);
	return (new);
}

t_dictionary	*initialize_env(char **env_arg)
{
	int				i;
	t_dictionary	*new;
	t_dictionary	*previous;
	t_dictionary	*first;

	previous = NULL;
	first = ft_calloc(sizeof(t_dictionary), 1);
	i = 0;
	while (env_arg[i] != NULL)
	{
		new = create_env_node(env_arg[i]);
		new->previous = previous;
		if (previous)
			previous->next = new;
		else
		{
			first->next = new;
			new->previous = first;
		}
		previous = new;
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
