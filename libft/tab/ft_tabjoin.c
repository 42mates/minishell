/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:40:08 by mbecker           #+#    #+#             */
/*   Updated: 2024/02/23 16:10:41 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tab.h"

/**
 * adds a string to a string array and returns the resulting array.
 *
 * @param tab The array to join the string to.
 * @param str The string to be joined to the array.
 * @param free_tab 1/TRUE to free tab after concatenation, 0/FALSE otherwise.
 * @param free_str 1/TRUE to free s1 after concatenation, 0/FALSE otherwise.
 * @return The resulting string array after joining the string.
 */
char	**ft_tabjoin(char **tab, char *str, int free_tab, int free_str)
{
	size_t	tablen;
	char	**res;
	int		i;

	if (tab == NULL || str == NULL)
		return (tab);
	tablen = ft_tablen((const char **)tab);
	res = (char **)malloc(sizeof(char *) * (tablen + 2));
	if (!res)
		return (NULL);
	i = -1;
	while (tab[++i])
		res[i] = ft_strdup(tab[i]);
	res[tablen] = ft_strdup(str);
	res[tablen + 1] = NULL;
	if (free_tab)
		freetab(tab, 1);
	if (free_str)
		free(str);
	return (res);
}
