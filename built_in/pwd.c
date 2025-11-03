/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:35:28 by matoledo          #+#    #+#             */
/*   Updated: 2025/10/29 21:18:47 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	pwd()
{
	size_t	size;
	char	*directory;
	
	size = 512;
	directory = getcwd(NULL, size);
	if (directory == NULL)
		perror("Error");
	printf("%s\n", directory);
	free(directory);
}
