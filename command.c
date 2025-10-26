/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:51:47 by matoledo          #+#    #+#             */
/*   Updated: 2025/10/26 15:17:14 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution_shell.h"
# include "built_in/built_in.h"

void	search_built_in_command(char *command, char **arguments)
{
	if(start_with(command, "echo") == 0)
		echo(arguments);
	if(start_with(command, "cd") == 0)
		printf("por desarrollar");
	if(start_with(command, "pwd") == 0)
		printf("por desarrollar");
	if(start_with(command, "export") == 0)
		printf("por desarrollar");
	if(start_with(command, "unset") == 0)
		printf("por desarrollar");		
	if(start_with(command, "env") == 0)
		printf("por desarrollar");	
	if(start_with(command, "exit") == 0)
			printf("por desarrollar");
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

char	*search_bash_command(char *command, char **environment)
{
	char	**divided_path;
	char	*joined_path;
	char	*joined_path2;

	divided_path = split(environment[0] + 5, ':');
	while (*divided_path)
	{
		joined_path2 = ft_strcat(*divided_path, "/");
		joined_path = ft_strcat(joined_path2, command);
		free(joined_path2);
		if (access(joined_path, F_OK) == 0)
			break ;
		free(joined_path);
		joined_path = NULL;
		divided_path++;
	}
	return (joined_path);
}

void	execute_bash_command(char *command, char **arguments, char **environment)
{
	char	*command_path;

	command_path = search_bash_command(command, environment);
	if (!command_path)
	{
		perror(command);
		return ;
	}
	if (execve(command_path, arguments, environment) == -1)
	{
		perror(command);
		exit (1);
	}
}

void	execute_command(char *command, char **arguments, char **environment)
{
	//implementar la redirección de pipes y generación de hijos
	if (execute_built_in_command(command, arguments) == 1)
		execute_bash_command(command, arguments, environment);
}