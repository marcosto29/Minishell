/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:07:34 by matoledo          #+#    #+#             */
/*   Updated: 2026/02/05 20:06:25 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(void)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	modify_key_value("OLDPWD", find_key("PWD"));
	modify_key_value("PWD", new_pwd);
	free(new_pwd);
}

int	cd(char **args)
{
	char	*dir;

	if (ft_size_dc(args) > 1)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (!*args)
		dir = ft_strdup(find_key("HOME"));
	else
		dir = ft_strdup(args[0]);
	if (!dir)
		return (1);
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(dir);
		return (1);
	}
	change_directory();
	free(dir);
	return (0);
}
