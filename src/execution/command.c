/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:51:47 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/14 18:01:24 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_built_in_command(char *command, char **args)
{
	args += 1;
	if (start_with(command, "echo") == 0)
		echo(args);
	if (start_with(command, "cd") == 0)
		cd(args);
	if (start_with(command, "pwd") == 0)
		pwd();
	if (start_with(command, "export") == 0)
		export(args);
	if (start_with(command, "unset") == 0)
		printf("por desarrollar\n");
	if (start_with(command, "env") == 0)
		printf("por desarrollar\n");
	if (start_with(command, "exit") == 0)
		printf("por desarrollar\n");
}

//echo, cd, pwd, export, unset, env, exit
int	execute_built_in_command(char *command, char **arguemnts)
{
	static char	**built_in_list;

	if (!built_in_list)
		built_in_list = (char *[]){"echo", "cd", "pwd", "export",
			"unset", "env", "exit", NULL};
	if (contains_string(built_in_list, command) == 0)
	{
		search_built_in_command(command, arguemnts);
		return (0);
	}
	return (1);
}

char	*search_bash_command(char *command)
{
	char	**divided_path;
	char	**aux;
	char	*joined_path;
	char	*joined_path2;

	divided_path = split(find_key("PATH", NULL), ':');
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

void	execute_bash_command(char *command, char **args)
{
	char	*command_path;
	pid_t	p;

	p = fork();
	if (p != 0)
	{
		command_path = search_bash_command(command);
		if (!command_path)
			perror(command);
		if (execve(command_path, args,
				dict_to_list(environment("get", NULL, NULL))) == -1)
			perror(command);
	}
	wait(NULL);
}

void	execute_command(char *command, char **args)
{
	if (execute_built_in_command(command, args) == 1)
		execute_bash_command(command, args);
}
