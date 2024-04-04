/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:02:33 by mbecker           #+#    #+#             */
/*   Updated: 2024/03/29 17:26:47 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

/**
 * @brief Frees a char **tab and its content.
 * @param tab The tab to free.
 * @param heap If 1, frees the tab itself.
 */
void	freetab(char **tab, int heap)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (heap)
		free(tab);
}
