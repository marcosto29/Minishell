/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_shell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:52:00 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/14 12:29:34 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_SHELL_H
# define EXECUTION_SHELL_H
# include <unistd.h>

typedef struct dictionary
{
	void					*key;
	void					*value;
	struct dictionary		*previous;
	struct dictionary		*next;
}	t_dictionary;

size_t			ft_size(void *pointer, size_t data_type);
size_t			ft_size_dc(char **double_a);
size_t			ft_dict_size(t_dictionary *dict);
void			*ft_calloc(size_t type, size_t size);
char			**split(char *string, char divider, int ammount);
char			*ft_str_new(char *string);
void			ft_strlcopy(char *to_copy, char *copied);
char			*ft_strcat(char *string1, char *string2);
int				start_with(char	*string, char *find);
int				execute_command(char *command, char **arguments,
								int fdi, int fdo);
int				contains_string(char **string_list, char *string);
void			free_double(char ***pointer);
t_dictionary	*environment(char *operation, char **env_arg);
char			**dict_to_list(t_dictionary *dict);
char			*find_key(char *str);
void			add_key_value(char *key, char *value);
void			remove_key_value(char *key);
void			modify_key_value(char *key, char *value);
void			show_environment();
void			free_environment();
void			minishell_loop();
int	is_built_in_command(char *command);
int	execute_built_in_command(char *command, char **args);
#endif