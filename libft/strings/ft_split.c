/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:10:50 by mbecker           #+#    #+#             */
/*   Updated: 2024/03/29 17:33:53 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

size_t	avoid_char(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] && s[i] == c)
	{
		count++;
		i++;
	}
	return (count);
}

/**
 * splits the string s into words, separated by a given char c.
 * allocates and returns a NULL-terminated array of strings (words).
 */
char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	res = (char **)malloc(ft_wordcount(s, c) * sizeof(char *));
	if (!res)
		return (0);
	while (j < ft_wordcount(s, c) - 1)
	{
		i += avoid_char(s, c, i);
		start = i;
		while (s[i] && s[i] != c)
			i++;
		res[j] = ft_strndup((s + start), i - start);
		if (!res[j])
			freetab(res, TRUE);
		j++;
	}
	res[j] = NULL;
	return (res);
}

size_t	avoid_charset(char const *s, char *charset, int i)
{
	int	count;

	count = 0;
	while (s[i] && ft_strchr(charset, s[i]))
	{
		count++;
		i++;
	}
	return (count);
}

/**
 * splits the string s into words, separated by a given char c.
 * allocates and returns a NULL-terminated array of strings (words).
 */
char	**ft_split_charset(char const *s, char *charset)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	res = (char **)malloc(ft_wordcount_cset(s, charset) * sizeof(char *));
	if (!res)
		return (0);
	while (j < ft_wordcount_cset(s, charset) - 1)
	{
		i += avoid_charset(s, charset, i);
		start = i;
		while (s[i] && !ft_strchr(charset, s[i]))
			i++;
		res[j] = ft_strndup((s + start), i - start);
		if (!res[j])
			freetab(res, TRUE);
		j++;
	}
	res[j] = NULL;
	return (res);
}
