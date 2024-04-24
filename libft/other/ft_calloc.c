/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:21:51 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/22 15:18:49 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ub;
	unsigned char	uc;

	ub = b;
	uc = c;
	while (len > 0)
	{
		*ub = uc;
		ub++;
		len--;
	}
	return (b);
}

/**
 * Allocates memory for an array of elements and initializes them to zero.
 *
 * @param nmemb The number of elements to allocate.
 * @param size The size of each element.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	memsize;

	memsize = nmemb * size;
	if (size && memsize / size != nmemb)
		return (NULL);
	res = (char *)malloc(memsize);
	if (!res)
		return (NULL);
	ft_memset(res, 0, memsize);
	return (res);
}
