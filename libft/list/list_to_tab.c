/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:46:33 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/28 12:42:00 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * Converts a linked list to an array of strings under the `env` format.
 *
 * @param list The linked list to convert.
 * @return A null-terminated array of strings representing the linked list.
 *         Returns NULL if memory allocation fails.
 */
char	**list_to_env(t_list *list)
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

/**
 * Converts the values of all nodes `lst` to an array of strings.
 *
 * @param lst The linked list to convert.
 * @return the array or NULL if memory allocation fails.
 */
char	**list_to_argv(t_list *lst)
{
	char	**argv;
	t_elem	*node;
	int		i;

	argv = malloc(sizeof(char *) * (list_size(lst) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	node = lst->head;
	while (node)
	{
		argv[i++] = node->val;
		node = node->next;
	}
	argv[i] = NULL;
	return (argv);
}
