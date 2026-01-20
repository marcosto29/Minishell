/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:07:34 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/19 22:23:58 by matoledo         ###   ########.fr       */
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

	if (!*args)
	{
		dir = ft_strdup(find_key("HOME"));
		if (!dir)
			return (1);
	}
	else
		dir = ft_strdup(args[0]);
	if (ft_size_dc(args) > 1)
	{
		printf("cd: too many arguments\n");
		free(dir);
		return (1);
	}
	if (chdir(dir) == -1)
		printf("cd: %s: %s\n", dir, strerror(errno));
	else
		change_directory();
	free(dir);
	return (0);
}
