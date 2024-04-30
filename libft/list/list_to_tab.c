/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:46:33 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/29 16:46:35 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

char	**list_to_tab(t_list *list)
{
	char	**tab;
	t_elem	*node;
	int		i;

	tab = malloc(sizeof(char *) * (list_size(list) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	node = list->head;
	while (node)
	{
		tab[i] = ft_strjoin(node->key, "=", FALSE, FALSE);
		if (node->val)
			tab[i] = ft_strjoin(tab[i], node->val, TRUE, FALSE);
		if (!tab[i])
			return (freetab(tab, TRUE), NULL);
		node = node->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
