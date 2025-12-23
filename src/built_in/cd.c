/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:07:34 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/23 20:35:13 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	change_directory(int home, char *new_dir)
{
	char	*new_pwd;
	char	*tmp;

	modify_key_value("OLDPWD", find_key("PWD"));
	if (home == 1)
		modify_key_value("PWD", find_key("HOME"));
	else
	{
		tmp = ft_strjoin(find_key("PWD"), "/");
		new_pwd = ft_strjoin(tmp, new_dir);
		modify_key_value("PWD", new_pwd);
		free(new_pwd);
		free(tmp);
	}
}

int	cd(char **args)
{
	char	*dir;
	int		home;
	
	home = 0;
	if (!*args)
	{
		home = 1;
		dir = ft_strdup(find_key("HOME"));
		if (!dir)
			return (0);
	}
	else
		dir = ft_strdup(args[0]);
	if (ft_size_dc(args) > 1)
	{
		printf("cd: too many arguments\n");
		free(dir);
		return (0);
	}
	if (chdir(dir) == -1)
		printf("cd: %s: %s\n", dir, strerror(errno));
	else
		change_directory(home, dir);
	free(dir);
	return (0);
}
