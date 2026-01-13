/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:51:47 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/13 20:03:58 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
		return (0);
	return (1);
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
		if (access(joined_path, X_OK) == 0 && is_file(joined_path) == 0)
			break ;
		free(joined_path);
		joined_path = NULL;
		divided_path++;
	}
	free_double(aux);
	return (joined_path);
}

// == 0 para hacer ejecución con padre != 0 para hacer ejecución con hijo
//(normalmente uso esta cuano necesito debuggear)
int	execute_bash_command(char *command, char **args, int fdi, int fdo)
{
	char	*command_path;
	char	**list_dictionary;
	pid_t	p;

	p = fork();
	if (p == 0)
	{
		command_path = search_bash_command(command);
		if (!command_path)
			printf("%s: command not found\n", command);
		else
		{
			list_dictionary = dict_to_list(environment("get", NULL));
			dup2(fdo, 1);
			dup2(fdi, 0);
			execve(command_path, args, list_dictionary);
			perror(command);
			free_double(list_dictionary);
		}
		free(command_path);
		exit (1);
	}
	wait(NULL);
	return (0);
}

int	execute_command(char *command, char **args, int fdi, int fdo)
{
	if (is_built_in_command(command) == 0)
		return (execute_built_in_command(command, args));
	else
		return (execute_bash_command(command, args, fdi, fdo));
	return (0);
}
