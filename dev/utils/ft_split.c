/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:29:10 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:07:07 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_get_array_size(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count + 1);
}

static char	*ft_get_next_word(int *index, const char *str, char c)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = 0;
	while (str[*index] == c)
		(*index)++;
	while (str[*index + len] && str[*index + len] != c)
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i++] = str[*index];
		*index = *index + 1;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		as;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	as = ft_get_array_size(s, c);
	res = malloc(as * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < as - 1)
		res[i++] = ft_get_next_word(&j, s, c);
	res[i] = 0;
	return (res);
}
