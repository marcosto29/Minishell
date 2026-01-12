/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:10:41 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/12 20:00:45 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo, cd, pwd, export, unset, env, exit
int	is_built_in_command(char *command)
{
	char	**built_in_list;

	built_in_list = (char *[]){"echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	return (contains_string(built_in_list, command));
}

int	execute_built_in_command(char *command, char **args)
{
	args += 1;
	if (start_with(command, "echo") == 0)
		return (echo(args));
	if (start_with(command, "cd") == 0)
		return (cd(args));
	if (start_with(command, "pwd") == 0)
		return (pwd());
	if (start_with(command, "export") == 0)
		return (export(args));
	if (start_with(command, "unset") == 0)
		return (unset(args));
	if (start_with(command, "env") == 0)
		return (env(args));
	if (start_with(command, "exit") == 0)
		return (-1);
	return (0);
}