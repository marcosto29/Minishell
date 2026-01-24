/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:51:47 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/24 11:38:24 by matoledo         ###   ########.fr       */
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

void	thread_execution(char *command, char **args)
{
	char	*command_path;
	char	**list_dictionary;

	command_path = search_bash_command(command);
	if (!command_path)
		printf("%s: command not found\n", command);
	else
	{
		list_dictionary = dict_to_list(environment("get", NULL));
		execve(command_path, args, list_dictionary);
		perror(command);
		free_double(list_dictionary);
	}
	free(command_path);
	exit (1);
}

// == 0 para hacer ejecución con padre != 0 para hacer ejecución con hijo
//(normalmente uso esta cuano necesito debuggear)
int	execute_bash_command(char *command, char **args)
{
	pid_t	p;
	int		status;

	g_global.in_cmd = 1;
	p = fork();
	if (p == 0)
		thread_execution(command, args);
	waitpid(p, &status, 0);
	init_signals();
	status = parse_status(status);
	exit_status("set", &status);
	g_global.in_cmd = 0;
	return (0);
}

int	execute_command(char *command, char **args, int fdi, int fdo)
{
	int	result;
	int	saved_in;
	int	saved_out;
	
	saved_in = dup(0);
	saved_out = dup(1);
	dup2(fdi, 0);
	dup2(fdo, 1);
	if (is_built_in_command(command) == 0)
		result = execute_built_in_command(command, args);
	else
		result = execute_bash_command(command, args);
	dup2(saved_out, 1);
	dup2(saved_in, 0);
	return (result);
}
