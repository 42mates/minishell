/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:19:32 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:17:48 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/*
Returns ptr to allocated list or NULL.
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

/*
Returns ptr to allocated elemet or NULL.
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

/*
If list empty:	creates head.
Else 		 :	creates element at the end of list.
Returns 1 if OK.
Returns 0 if can't create new elem.
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

/*
Ony for lists with comporators!
Adds new element to empty list.
If list contains element with the same key,
destructs previous value and sets new value (just for 1st same key).
If no elements with the same key, adds new element at the end of list.
Returns 1 if OK (replaced or added).
Returns 0 if list == NULL or cat't add new element.
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
