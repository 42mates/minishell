/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:59:29 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/24 17:35:25 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * Creates a duplicate of a given list.
 *
 * @param list The original list to be duplicated.
 * @param keydup A function pointer to a key duplication function.
 * @param valdup A function pointer to a value duplication function.
 * @return A new list that is a duplicate of the original list,
	with duplicated keys and values.
 */
t_list	*list_dup(t_list *list, void *(keydup)(void *), void *(valdup)(void *))
{
	t_list	*new_list;
	t_elem	*current;

	if (!list)
		return (NULL);
	new_list = list_new(list->cmp_key, list->dst_key, list->dst_val);
	current = list->head;
	while (current)
	{
		list_put(new_list, keydup(current->key), valdup(current->val));
		current = current->next;
	}
	return (new_list);
}

/**
 * Duplicates a linked list of strings.
 *
 * This function creates a new linked list by duplicating each string element
 * in the given list using the `ft_strdup` function. The duplicated list will
 * have the same order of elements as the original list.
 *
 * @param list The original linked list to be duplicated.
 * @return A new linked list containing duplicated strings.
 */
t_list	*list_dup_str(t_list *list)
{
	return (list_dup(list, (void *(*)(void *))ft_strdup,
		(void *(*)(void *))ft_strdup));
}
