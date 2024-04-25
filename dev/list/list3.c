/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:19:32 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:19:46 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/*
Destructs keys and values, then frees element, then frees list. 
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
	while (e_curr)
	{
		e_next = e_curr->next;
		if (l->dst_key)
			l->dst_key(e_curr->key);
		if (l->dst_val)
			l->dst_val(e_curr->val);
		free(e_curr);
		e_curr = e_next;
	}
	free(l);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	cmp_str(const void *key_1, const void *key_2)
{
	return (ft_strcmp((const char *)key_1, (const char *)key_2));
}
