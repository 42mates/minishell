/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:32:42 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/18 16:39:23 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int cmp_int(const void *key_1, const void *key_2)
{
	return (*(int *)key_1 - *(int *)key_2);
}

int	cmp_str(const void *key_1, const void *key_2)
{
	return (ft_strcmp((const char *)key_1, (const char *)key_2));
}

// int		cmp_tok(const void *key_1, const void *key_2)
// {
// 	(void) key_1;
// 	(void) key_2;
// 	return (0); // okay, how to compare tokens ?
// }