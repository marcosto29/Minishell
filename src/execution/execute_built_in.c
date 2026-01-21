/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:10:41 by aosset-o          #+#    #+#             */
/*   Updated: 2026/01/20 21:50:34 by matoledo         ###   ########.fr       */
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
	int	exit_stat;

	args += 1;
	if (start_with(command, "echo") == 0)
		exit_stat = echo(args);
	if (start_with(command, "cd") == 0)
		exit_stat = cd(args);
	if (start_with(command, "pwd") == 0)
		exit_stat = pwd();
	if (start_with(command, "export") == 0)
		exit_stat = export(args);
	if (start_with(command, "unset") == 0)
		exit_stat = unset(args);
	if (start_with(command, "env") == 0)
		exit_stat = env(args);
	if (start_with(command, "exit") == 0)
		return (-1);
	exit_status("set", &exit_stat);
	return (exit_stat);
}
