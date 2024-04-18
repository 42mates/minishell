/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:19:32 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/18 16:12:49 by mbecker          ###   ########.fr       */
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
	if (curr->val)
		free(curr->val);
	if (curr->key)
		free(curr->key);
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

/*
Destructs keys and values, then frees element, then frees list.
*/
void	list_free(t_list *list)
{
	t_elem	*e_curr;
	t_elem	*e_next;

	if (!list)
		return ;
	e_curr = list->head;
	while (e_curr)
	{
		e_next = e_curr->next;
		if (list->dst_key)
			list->dst_key(e_curr->key);
		if (list->dst_val)
			list->dst_val(e_curr->val);
		free(e_curr);
		e_curr = e_next;
	}
	free(list);
}

/*
Comporators.
Do we need another comparator?
*/
int	cmp_int(const void *key_1, const void *key_2)
{
	int	*a;
	int	*b;

	a = (int *)key_1;
	b = (int *)key_2;
	return (*a - *b);
}

int	cmp_str(const void *key_1, const void *key_2)
{
	return (ft_strcmp((const char *)key_1, (const char *)key_2));
}

// int		cmp_tok(const void *key_1, const void *key_2)
// {
// 	(void) key_1;
// 	(void) key_2;
// 	return (0); // okay, how to compare tokens ?
// }
