/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:11:08 by matoledo          #+#    #+#             */
/*   Updated: 2025/10/21 23:53:27 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

size_t	ft_size(void *pointer, size_t data_type)
{
	size_t	size;

	size = 0;
	if (!pointer)
		return (size);
	while (*(char *)pointer)
	{
		size++;
		pointer++;
	}
	return (size / data_type);
}

void	*ft_calloc(size_t type, size_t size)
{
	void	*list;
	void	*aux;
	size_t	counter;

	counter = 0;
	list = malloc(type * size);
	aux = list;
	if (!list)
		return (NULL);
	while (counter < type * size)
	{
		*(char *)aux = '\0';
		aux++;
		counter++;
	}
	return (list);
}

void	string_split(char **splitted, char *to_split, char divider)
{
	int		divide_number;
	char	*aux;

	while (*to_split)
	{
		divide_number = 0;
		aux = to_split;
		while (*aux != divider && *aux)
		{
			divide_number++;
			aux++;
		}
		*splitted = ft_calloc(sizeof(char), divide_number + 1);
		aux = *splitted;
		while (*to_split != divider && *to_split)
		{
			*aux = *to_split;
			aux++;
			to_split++;
		}
		splitted++;
		to_split++;
	}
}

char	**split(char *string, char divider)
{
	int		divide_number;
	char	**splitted_word;
	char	**aux2;
	char	*aux;

	divide_number = 1;
	aux = string;
	while (*aux)
	{
		if (*aux == divider)
			divide_number++;
		aux++;
	}
	splitted_word = ft_calloc(sizeof(char *), divide_number + 1);
	string_split(splitted_word, string, divider);
	return (splitted_word);
}

char	*ft_str_new(char *string)
{
	int		size;
	char	*new_string;
	char	*aux;

	size = ft_size(string, sizeof(char));
	new_string = ft_calloc(sizeof(char), size + 1);
	aux = new_string;
	while (*string)
	{
		*aux = *string;
		aux++;
		string++;
	}
	return (new_string);
}

void	ft_strlcopy(char *to_copy, char *copied)
{
	while (*copied)
	{
		*to_copy = *copied;
		to_copy++;
		copied++;
	}
}

char	*ft_strcat(char *string1, char *string2)
{
	char	*total_string;
	size_t	total_size;

	total_size = 0;
	total_size += ft_size(string1, sizeof(char));
	total_size += ft_size(string2, sizeof(char));
	total_string = ft_calloc(sizeof(char), total_size + 1);
	ft_strlcopy(total_string, string1);
	ft_strlcopy(total_string + ft_size(total_string, sizeof(char)), string2);
	return (total_string);
}

char	*access_to_file(char *command, char **environment)
{
	char	**divided_path;
	char	*joined_path;
	char	*aux;
	char	*separator;
	int		i;

	divided_path = split(environment[0] + 5, ':');
	while(*divided_path)
	{
		joined_path = ft_strcat(*divided_path, "/");
		joined_path = ft_strcat(joined_path, command);
		if (access(joined_path, F_OK) == 0)
			break;
		free(joined_path);
		joined_path = NULL;
		divided_path++;
	}
	return (joined_path);
}

void	execute_command(char *command, char **arguments, char **enviroment)
{
	char	*command_path;

	command_path = access_to_file(command, enviroment);
	if (!command_path)
	{
		perror(command);
		return ;
	}
	if (execve(command_path, arguments, enviroment) == -1)
	{
		perror(command);
		exit (1);
	}
}

int	start_with(char	*string, char *find)
{
	while (*find)
	{
		if (*string != *find)
			return (1);
		string++;
		find++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char	**path;
	int		i;

	i = argc + 1;
	path = ft_calloc(sizeof(char *), 2);
	while (argv[i] && start_with(argv[i], "PATH") == 1)
		i++;
	*path = ft_str_new(argv[i] + 5);
	path[1] = NULL;
	if (!path)
	{
		printf("PATH not found\n");
		return (1);
	}
	execute_command("t", NULL, path);
}
