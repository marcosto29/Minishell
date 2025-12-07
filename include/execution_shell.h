/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_shell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:52:00 by matoledo          #+#    #+#             */
/*   Updated: 2025/11/11 20:10:21 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_SHELL_H
# define EXECUTION_SHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

typedef	struct dictionary
{
	void	*key;
	void	*value;
}	t_dictionary;

size_t			ft_size(void *pointer, size_t data_type);
void			*ft_calloc(size_t type, size_t size);
char			**split(char *string, char divider);
char			*ft_str_new(char *string);
void			ft_strlcopy(char *to_copy, char *copied);
char			*ft_strcat(char *string1, char *string2);
int				start_with(char	*string, char *find);
void			execute_command(char *command, char **arguments, char **environment);
int				contains_string(char **string_list, char *string);
void			free_double(char **pointer);
t_dictionary	**environment(char *operation, char **env_arg, t_dictionary **dict_env);

#endif