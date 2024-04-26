/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:37:19 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/24 12:02:29 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (!us1 && !us2)
		return (0);
	else if (!us1)
		return (-us2[0]);
	else if (!us2)
		return (us1[0]);
	while (us1[i] || us2[i])
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (!us1 && !us2)
		return (0);
	else if (!us1)
		return (-us2[0]);
	else if (!us2)
		return (us1[0]);
	while ((us1[i] || us2[i]) && n > i)
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (0);
}
