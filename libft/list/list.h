/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:15:47 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/29 16:46:48 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../libft.h"

typedef int		(*t_cmp_key)(const void *key_1, const void *key_2);
typedef void	(*t_dst_key)(void *key);
typedef void	(*t_dst_val)(void *val);

/**
 * An element in the `t_list` linked list.
 *
 * void *`next` - The next element in the linked list.
 * void *`key` - The key associated with the element.
 * void *`val` - The value associated with the element.
 */
typedef struct s_elem
{
	void		*next;
	void		*key;
	void		*val;
}				t_elem;

/**
 * The linked list
 *
 * t_elem* `head` - Pointer to the head element of the linked list.
 * t_cmp_key `cmp_key` - Function pointer for comparing keys in the list.
 * t_dst_key `dst_key` - Function pointer for destroying keys in the list.
 * t_dst_val `dst_val` - Function pointer for destroying values in the list.
 */
typedef struct s_list
{
	t_elem		*head;
	t_cmp_key	cmp_key;
	t_dst_key	dst_key;
	t_dst_val	dst_val;
}				t_list;

t_list	*list_new(t_cmp_key cmp_key, t_dst_key dst_key, t_dst_val dst_val);
int		list_put(t_list *list, void *key, void *val);
int		list_replace(t_list *list, void *key, void *new_val);
int		list_del_one(t_list *list, void *key);
int		list_size(t_list *list);
void	*list_get(t_list *list, void *key);
t_elem	*list_get_elem(t_list *list, void *key);
void	list_free(t_list *list);

int		cmp_int(const void *key_1, const void *key_2);
int		cmp_str(const void *key_1, const void *key_2);
// int		cmp_tok(const void *key_1, const void *key_2);

t_list	*tab_to_list(char **tab);
char	**list_to_tab(t_list *list);


t_list	*list_dup(t_list *list, void *(keydup)(void *), void *(valdup)(void *));
t_list	*list_dup_str(t_list *list);

#endif