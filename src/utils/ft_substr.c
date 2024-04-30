/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:09:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:07:08 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		res = (char *) malloc(sizeof(char) * (1));
	else if (s_len - start > len)
		res = (char *) malloc(sizeof(char) * (len + 1));
	else
		res = (char *) malloc(sizeof(char) * (s_len - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (start + i < s_len && s[start + i] && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
