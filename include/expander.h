/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosset-o <aosset-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:21:06 by aosset-o          #+#    #+#             */
/*   Updated: 2026/02/05 10:26:40 by aosset-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

char	*expander(char *str);
char	*dollar_value(char *str);
size_t	calculate_total_len(const char *str);
int		dollar_sign(char *str);
#endif