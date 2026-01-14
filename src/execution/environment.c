/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:01 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/14 12:30:07 by aosset-o         ###   ########.fr       */
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
		free_double(&splitted_arg);
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
