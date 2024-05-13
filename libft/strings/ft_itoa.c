/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:10:08 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/14 13:11:09 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

static void	ft_revert_inttab(char *s)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(s) - 1;
	if (s[start] == '-')
		start++;
	while (start < end)
	{
		temp = s[start];
		s[start++] = s[end];
		s[end--] = temp;
	}
}

char	*ft_itoa(int n)
{
	char		*res;
	long long	ln;
	int			i;

	i = 0;
	ln = n;
	res = (char *)malloc(ft_numlen(ln) + 1);
	if (!res)
		return (NULL);
	if (ln == 0)
		res[i++] = '0';
	if (ln < 0)
	{
		res[i++] = '-';
		ln = -ln;
	}
	while (ln > 0)
	{
		res[i++] = (ln % 10) + 48;
		ln /= 10;
	}
	res[i] = 0;
	ft_revert_inttab(res);
	return (res);
}

char	*ft_uitoa(unsigned int n)
{
	unsigned int	buf;
	unsigned int	i;
	char			*res;

	buf = n;
	i = 0;
	while (buf)
	{
		i++;
		buf = buf / 10;
	}
	if (i == 0)
		i = 1;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (NULL == res)
		return (NULL);
	res[i] = '\0';
	while (i--)
	{
		res[i] = n % 10 + '0';
		n = n / 10;
	}
	return (res);
}
