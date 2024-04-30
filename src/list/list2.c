/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:19:32 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:19:13 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/list.h"

/*
Relinks elements.
Destructs and free node.
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

/*
Returns 0 if list == NULL.
Returns 1 if node was deleted or if didn't find node with the same key.
*/
int	list_del(t_list *list, void *key)
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
	return (1);
}

/*
Returnes list size or 0 for empty list
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

/*
Returns 1 if the list contains the key.
Returns 0 if not.
*/
int	list_contains_key(t_list *list, void *key)
{
	t_elem	*e_ptr;

	if (!list || list_size(list) == 0)
		return (0);
	e_ptr = list->head;
	while (e_ptr)
	{
		if (list->cmp_key(e_ptr->key, key) == 0)
			return (1);
		e_ptr = e_ptr->next;
	}
	return (0);
}

/*
Returns ptr to a value from the list according the key.
Returns NULL if list emty or no key in list.
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
