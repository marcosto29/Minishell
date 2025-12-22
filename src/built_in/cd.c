/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:07:34 by matoledo          #+#    #+#             */
/*   Updated: 2025/12/22 16:29:18 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	change_directory(char *new_dir)
{
	char	*new_pwd;
	char	*tmp;

	find_key("OLDPWD", find_key("PWD", NULL));
	tmp = ft_strjoin(find_key("PWD", NULL), "/");
	new_pwd = ft_strjoin(tmp, new_dir);
	find_key("PWD", new_pwd);
	free(new_pwd);
	free(tmp);
}

int	cd(char **args)
{
	char	*dir;
	
	if (!*args)
	{
		dir = find_key("HOME", NULL);
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
	change_directory(dir);
	free(dir);
	return (0);
}
