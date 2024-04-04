/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:40:08 by mbecker           #+#    #+#             */
/*   Updated: 2024/03/29 17:33:54 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

char	*joincat(char *s1, char *s2, char *res)
{
	while (*s1)
	{
		*res = *s1;
		s1++;
		res++;
	}
	while (*s2)
	{
		*res = *s2;
		s2++;
		res++;
	}
	return (res);
}

/**
 * Concatenates two strings and returns the result.
 * The function allocates memory for the resulting string.
 * If either of the input strings is NULL, the function returns NULL.
 *
 * @param s1 The first string to be concatenated.
 * @param s2 The second string to be concatenated.
 * @param free_s1 1/TRUE to free s1 after concatenation, 0/FALSE otherwise.
 * @param free_s2 1/TRUE to free s2 after concatenation, 0/FALSE otherwise.
 * @return The concatenated string, or NULL if an error occurred.
 */
char	*ft_strjoin(char *s1, char *s2, int free_s1, int free_s2)
{
	size_t	l1;
	size_t	l2;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = (char *)malloc(l1 + l2 + 1);
	if (!res)
		return (NULL);
	res = joincat(s1, s2, res);
	*res = 0;
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (res - l1 - l2);
}
