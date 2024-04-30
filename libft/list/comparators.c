/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:32:42 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/30 16:31:31 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	cmp_int(const void *key_1, const void *key_2)
{
	int	*a;
	int	*b;

	a = (int *)key_1;
	b = (int *)key_2;
	return (*a - *b);
}

int	cmp_str(const void *key_1, const void *key_2)
{
	return (ft_strcmp((const char *)key_1, (const char *)key_2));
}
