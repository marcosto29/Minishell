/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_shell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:52:00 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/09 21:28:41 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_SHELL_H
# define EXECUTION_SHELL_H
#include <unistd.h>
typedef	struct dictionary
{
	void	*key;
	void	*value;
}	t_dictionary;

size_t			ft_size(void *pointer, size_t data_type);
size_t			ft_size_dc(char **double_a);
size_t			ft_dict_size(t_dictionary **dict);
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
char			**dict_to_list(t_dictionary **dict);
char *find_key(char *str);
#endif