/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:21:51 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_str_concat(const char *s1, char c, const char *s2, char use_c)
{
	int			i;
	const int	r_len = ft_strlen(s1) + (use_c != 0) + ft_strlen(s2);
	char		*res;

	res = (char *)malloc(sizeof(char) * (r_len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s1 && *s1)
	{
		res[i] = *s1;
		i++;
		s1++;
	}
	if (use_c)
		res[i++] = c;
	while (s2 && *s2)
	{
		res[i] = *s2;
		i++;
		s2++;
	}
	res[i] = '\0';
	return (res);
}
