/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:51:47 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/04 13:56:15 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//echo, cd, pwd, export, unset, env, exit
int	is_built_in_command(char *command)
{
	char	**built_in_list;

	built_in_list = (char *[]){"echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	return (contains_string(built_in_list, command));
}

char	*search_bash_command(char *command)
{
	char	**divided_path;
	char	**aux;
	char	*joined_path;
	char	*joined_path2;

	if (access(command, F_OK) == 0)
		return (command);
	divided_path = split(find_key("PATH"), ':', -1);
	if (!divided_path)
		return (NULL);
	aux = divided_path;
	while (*divided_path)
	{
		joined_path2 = ft_strcat(*divided_path, "/");
		joined_path = ft_strcat(joined_path2, command);
		free(joined_path2);
		joined_path2 = NULL;
		if (access(joined_path, F_OK) == 0)
			break ;
		free(joined_path);
		joined_path = NULL;
		divided_path++;
	}
	free_double(aux);
	return (joined_path);
}

void	not_command(char *command)
{
	if (ft_strchr(command, '/') != NULL)
		printf("%s: No such file or directory\n", command);
	else
		printf("%s: command not found\n", command);
}

// == 0 para hacer ejecución con padre != 0 para hacer ejecución con hijo
//(normalmente uso esta cuano necesito debuggear)
int	execute_bash_command(char *command, char **args)
{
	char	*command_path;
	char	**list_dictionary;
	pid_t	p;

	p = fork();
	if (p == 0)
	{
		command_path = search_bash_command(command);
		if (!command_path)
		{
			not_command(command);
			exit (0);
		}
		list_dictionary = dict_to_list(environment("get", NULL));
		execve(command_path, args, list_dictionary);
		perror(command);
		free_double(list_dictionary);
		free(command_path);
		exit (1);
	}
	wait(NULL);
	return (0);
}

int	execute_command(char *command, char **args, int fdi, int fdo)
{
	(void)fdi;
	(void)fdo;
	if (is_built_in_command(command) == 0)
		return (execute_built_in_command(command, args));
	else
		return (execute_bash_command(command, args));
	return (0);
}
