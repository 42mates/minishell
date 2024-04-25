/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:10:08 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/25 19:34:26 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

/**
 * returns the length of a number.
 */
static short int	ft_numlen(long long num)
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
