/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:19:32 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/16 13:37:19 by akurochk         ###   ########.fr       */
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
	while (e_ptr->next != NULL)
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
		if (list->cmp_key(key, e_ptr->key) == 0)
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
		if (list->cmp_key(key, e_curr->key) == 0)
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
int	cmp_int(void *key_1, void *key_2)
{
	return ((int)key_1 - (int)key_2);
}

int	cmp_str(void *key_1, void *key_2)
{
	return (ft_strcmp((const char *)key_1, (const char *)key_2));
}
