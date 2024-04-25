/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:24:06 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:26:42 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_str_contains(const char *s, const char c)
{
	if (s)
	{
		while (*s)
		{
			if (*s == c)
				return (1);
			s++;
		}
	}
	return (0);
}

/*
Returns 0 if OK.
Returns 1 if error.
*/
int	ft_str_split(const char *s, const char *sep, char **dst1, char **dst2)
{
	int	i;
	int	j;

	if (!s || !sep)
		return (1);
	i = 0;
	while (s[i] && !ft_str_contains(sep, s[i]))
		i++;
	j = i;
	*dst1 = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst1)
		return (1);
	while (j--)
		(*dst1)[j] = s[j];
	(*dst1)[i] = '\0';
	if (!s[i])
		*dst2 = NULL;
	else
		*dst2 = ft_strdup(s + i + 1);
	if (dst2)
		return (0);
	free(*dst1);
	return (1);
}
