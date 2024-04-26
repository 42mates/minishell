/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:37:55 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/24 12:17:42 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	dest = malloc(len * sizeof(char));
	if (!dest)
		return (0);
	len = 0;
	while (src[len])
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = 0;
	return (dest);
}

char	*ft_strndup(const char *src, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (src[i] && i < size)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
