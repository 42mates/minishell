/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:19:32 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/30 16:25:48 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * Creates a new list with the specified comparison key, destination key, and
 * destination value.
 *
 * @param cmp_key The function used to compare elements in the list.
 * @param dst_key The function used to retrieve the key of an element in the
 * list.
 * @param dst_val The function used to retrieve the value of an element in the
 * list.
 * @return A pointer to the newly created list, or NULL if malloc failed.
 */
t_list	*list_new(t_cmp_key cmp_key, t_dst_key dst_key, t_dst_val dst_val)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->cmp_key = cmp_key;
	list->dst_key = dst_key;
	list->dst_val = dst_val;
	return (list);
}

/**
 * Creates a new element for a linked list.
 *
 * @param key The key of the element.
 * @param val The value of the element.
 * @return A pointer to the newly created element, or NULL if malloc fails.
 */
static t_elem	*elem_new(void *key, void *val)
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->key = key;
	elem->val = val;
	return (elem);
}

/**
 * Inserts a new element with the given key and value at the end of the list.
 * If the list is empty, the new element becomes the head of the list.
 *
 * @param list The list to insert the element into.
 * @param key The key of the new element.
 * @param val The value of the new element.
 * @return 1 if the element was successfully inserted, 0 otherwise.
 */
int	list_put(t_list *list, void *key, void *val)
{
	t_elem	*e_ptr;

	if (!list)
		return (0);
	if (!list->head)
	{
		list->head = elem_new(key, val);
		return (list->head != NULL);
	}
	e_ptr = list->head;
	while (e_ptr->next)
		e_ptr = e_ptr->next;
	e_ptr->next = elem_new(key, val);
	return (e_ptr->next != NULL);
}

/**
 * Add or replace the value associated with a given key in a linked list.
 *
 * @param list The linked list.
 * @param key The key to search for.
 * @param new_val The new value to replace the existing value with.
 * @return 1 if the replacement was successful, 0 otherwise.
 */
int	list_replace(t_list *list, void *key, void *new_val)
{
	t_elem	*e_ptr;

	if (!list)
		return (0);
	if (list_size(list) == 0)
		return (list_put(list, key, new_val));
	e_ptr = list->head;
	while (1)
	{
		if ((list->cmp_key(key, e_ptr->key)) == 0)
		{
			if (list->dst_val)
				list->dst_val(e_ptr->val);
			e_ptr->val = new_val;
			return (1);
		}
		if (e_ptr->next)
			e_ptr = e_ptr->next;
		else
			break ;
	}
	e_ptr->next = elem_new(key, new_val);
	return (e_ptr->next != NULL);
}

/**
 * Frees the memory allocated for a linked list and its elements.
 */
void	list_free(void *list)
{
	t_elem	*e_curr;
	t_elem	*e_next;
	t_list	*l;

	l = (t_list *)list;
	if (!list)
		return ;
	e_curr = l->head;
	while (e_curr != NULL)
	{
		e_next = e_curr->next;
		if (l->dst_key != NULL)
			l->dst_key(e_curr->key);
		if (l->dst_val != NULL)
			l->dst_val(e_curr->val);
		free(e_curr);
		e_curr = e_next;
	}
	free(l);
}
