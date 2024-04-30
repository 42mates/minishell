/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:36:48 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/25 12:42:17 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

//returns a pointer to the first occurence of c in str.
char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	else
		return (NULL);
}

//returns a pointer to the last occurence of c in str.
char	*ft_strrchr(const char *str, int c)
{
	const char	*last_occ;

	last_occ = NULL;
	if (!str)
		return (NULL);
	while (*str != 0)
	{
		if (*str == (char)c)
			last_occ = str;
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return ((char *)last_occ);
}

/**
 * Searches for the first occurrence of any character from the set 
 * in the given string. Just like strchr, but with a set of characters.
 *
 * @param s The string to search in.
 * @param set The set of characters to search for.
 * @return The ASCII value of the first character found in the set,
 *  or 0 if no match is found.
 */
char	*ft_strchrset(char *s, char *set)
{
	int	i;
	int	j;

	i = 0;
	if (!s || !set)
		return (NULL);
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j++])
				return (&s[i]);
		}
		i++;
	}
	return (NULL);
}
