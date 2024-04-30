/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:43:32 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/23 17:02:34 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * Deletes an element's content from a linked list. To use in list_del_one only.
 */
static void	elem_del(t_list *list, t_elem *curr, t_elem *prev)
{
	if (prev)
		prev->next = curr->next;
	else
		list->head = curr->next;
	if (list->dst_key)
		list->dst_key(curr->key);
	if (list->dst_val)
		list->dst_val(curr->val);
	free(curr);
}

/**
 * Deletes an element from the list based on the given key.
 *
 * @param list The list from which to delete the element.
 * @param key The key of the element to be deleted.
 * @return 1 if the element was successfully deleted, 0 otherwise.
 */
int	list_del_one(t_list *list, void *key)
{
	t_elem	*e_curr;
	t_elem	*e_prev;

	if (!list)
		return (0);
	if (list_size(list) == 0)
		return (1);
	e_curr = list->head;
	e_prev = NULL;
	while (e_curr)
	{
		if ((list->cmp_key(key, e_curr->key)) == 0)
		{
			elem_del(list, e_curr, e_prev);
			return (1);
		}
		e_prev = e_curr;
		e_curr = e_curr->next;
	}
	return (0);
}

/**
 * @return The size of the linked list `list`.
 */
int	list_size(t_list *list)
{
	int		size;
	t_elem	*curr;

	size = 0;
	if (!list)
		return (size);
	curr = list->head;
	while (curr)
	{
		curr = curr->next;
		size++;
	}
	return (size);
}

/**
 * Retrieves the value associated with the given key from a linked list.
 *
 * @param list The linked list to search in.
 * @param key The key to search for.
 * @return The value associated with the key, or NULL if the key is not found.
 */
void	*list_get(t_list *list, void *key)
{
	t_elem	*e_ptr;

	if (!list || list_size(list) == 0)
		return (NULL);
	e_ptr = list->head;
	while (e_ptr)
	{
		if (list->cmp_key(e_ptr->key, key) == 0)
			return (e_ptr->val);
		e_ptr = e_ptr->next;
	}
	return (NULL);
}

/**
 * Retrieves an element from a linked list based on a given key.
 *
 * @param list The linked list to search in.
 * @param key The key to match against the elements in the list.
 * @return A pointer to the matching element, or NULL if no match is found.
 */
t_elem	*list_get_elem(t_list *list, void *key)
{
	t_elem	*e_ptr;

	if (!list || list_size(list) == 0)
		return (NULL);
	e_ptr = list->head;
	while (e_ptr)
	{
		if (list->cmp_key(e_ptr->key, key) == 0)
			return (e_ptr);
		e_ptr = e_ptr->next;
	}
	return (NULL);
}
