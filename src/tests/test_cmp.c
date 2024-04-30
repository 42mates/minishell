/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:24:46 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/17 15:57:24 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	cmp_int(const void *key_1, const void *key_2)
{
	int	*a;
	int	*b;

	a = (int *)key_1;
	b = (int *)key_2;
	return (*a - *b);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	cmp_str(const void *key_1, const void *key_2)
{
	return (ft_strcmp((const char *)key_1, (const char *)key_2));
}

/*
===CMP STR===
*/
int	main(int ac, char **av)
{
	if (ac != 3)
		return (1);	
	printf("a   = %s\nb   = %s\ncmp = %d\n", av[1], av[2], cmp_str(av[1], av[2]));
	return (0);
}


/*
===CMP INT===
*/
// int	main(int ac, char **av)
// {
// 	if (ac != 3)
// 		return (1);	
// 	int a = atoi(av[1]);
// 	int b = atoi(av[2]);
// 	printf("a   = %d\nb   = %d\ncmp = %d\n", a, b, cmp_int(&a, &b));
// 	return (0);
// }