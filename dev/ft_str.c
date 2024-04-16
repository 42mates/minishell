/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:51:38 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/16 14:28:00 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strcpy(char *dst, const char *src)
{
	int	i;
	int	s_len;

	i = -1;
	s_len = ft_strlen(src);
	if (s_len > 0)
	{
		while (++i < s_len - 1)
			dst[i] = src[i];
		dst[i] = 0;
	}
	return (s_len);
}


