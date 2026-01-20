/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matoledo <matoledo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:39:29 by matoledo          #+#    #+#             */
/*   Updated: 2026/01/20 19:54:19 by matoledo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

int	echo(char **args);
int	cd(char **args);
int	pwd(void);
int	export(char **args);
int	env(char **args);
int	unset(char **args);
int	own_exit(char **args);

#endif