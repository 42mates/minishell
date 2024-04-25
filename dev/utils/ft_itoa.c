/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:34:19 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:07:06 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_malloc_res(char *array)
{
	char	*result;
	int		end;
	int		i;

	end = ft_strlen(array);
	result = malloc(sizeof(char) * (end + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (--end >= 0)
		result[i++] = array[end];
	result[i] = 0;
	return (result);
}

static char	*ft_malloc_zero(void)
{
	char	*r;

	r = malloc(sizeof(char) * 2);
	if (!r)
		return (NULL);
	r[0] = '0';
	r[1] = 0;
	return (r);
}

char	*ft_itoa(int n)
{
	char			res[12];
	int				i;
	int				sign;
	long int		nb;

	if (n == 0)
		return (ft_malloc_zero());
	nb = (long int)n;
	sign = 1;
	if (nb < 0)
	{
		sign *= -1;
		nb = -nb;
	}
	i = 0;
	while (nb)
	{
		res[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	if (sign == -1)
		res[i++] = '-';
	res[i] = 0;
	return (ft_malloc_res(res));
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
