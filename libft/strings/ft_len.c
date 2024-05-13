/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:38:31 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/13 18:01:35 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

/***
 * returns the length of a string.
 * @note doesn't count the null-terminating character.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * Returns the length of a null-terminated array of strings.
 *
 * @param tab The array of strings.
 * @return The length of the array.
 */
size_t	ft_tablen(const char **tab)
{
	size_t	i;

	if (!tab || !*tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/**
 * Returns the number of digits in `num` 
 * @note 420 numlen = 3.
 */
int	ft_numlen(long long num)
{
	short int			len;

	len = 1;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num >= 10)
	{
		len++;
		num /= 10;
	}
	return (len);
}
