/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:03:13 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/19 22:22:47 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WSTOPSIG(status));
}

int	*exit_status(char *operation, int *new_stat)
{
	static int	*status;

	if (!status)
		status = ft_calloc(sizeof(int), 1);
	if (start_with(operation, "get") == 0)
		return (status);
	else if(start_with(operation, "set") == 0)
		*status = *new_stat;
	return (NULL);
}