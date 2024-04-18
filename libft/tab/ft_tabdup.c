/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:37:55 by mbecker           #+#    #+#             */
/*   Updated: 2024/02/23 16:11:00 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tab.h"

char	**ft_tabdup(char **tab)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new_tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			freetab(new_tab, TRUE);
			return (0);
		}
		i++;
	}
	new_tab[i] = 0;
	return (new_tab);
}
