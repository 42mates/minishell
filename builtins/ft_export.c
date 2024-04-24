/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:39:16 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/24 17:56:27 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/**
 * Deletes an element's content from a linked list. To use in list_del_onex only.
 */
static void	elem_delx(t_list *list, t_elem *curr, t_elem *prev)
{
	if (prev)
		prev->next = curr->next; //DELETE THIS FUNCTION
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
int	list_del_onex(t_list *list, void *key)
{
	t_elem	*e_curr;
	t_elem	*e_prev;

	if (!list)
		return (0);
	if (list_size(list) == 0) // DELELTE THIS FUNCTION
		return (1);
	e_curr = list->head;
	e_prev = NULL;
	while (e_curr)
	{
		if ((list->cmp_key(key, e_curr->key)) == 0)
		{
			elem_delx(list, e_curr, e_prev);
			return (1);
		}
		e_prev = e_curr;
		e_curr = e_curr->next;
	}
	return (0);
}

void	print_export(t_list *env)
{
	t_elem	*node;
	t_elem	*print;
	int		size;
	
	env = list_dup_str(env);
	size = list_size(env);
	while (size--)
	{
		node = env->head;
		print = env->head;
		while (node)
		{
			if (ft_strcmp(print->key, node->key) > 0)
				print = node;
			node = node->next;
		}
		//if (!(!ft_strcmp(print->key, "_") && !ft_strcmp(print->val, "export")))
		if (!(!ft_strcmp(print->key, "_") && !ft_strcmp(print->val, "./exe"))) //DELETE ME
			print_var(print, "export ");
		list_del_onex(env, print->key);
	}
	list_free(env);
}

int	get_key_val(char *arg, char **key, char **val)
{
	char	*sep;
	char	*quote;
	
	quote = ft_strchr(arg, '\'');
	sep = ft_strchr(arg, '=');
	if (!*arg || *arg == '=' || ft_isdigit(*arg) 
		|| (quote && (!sep || quote < sep)))
	
	//to refuse
	//"!@#%^&*()-+={}[]|:;'\",<>./?\\";
	
	//to ignore
	//" \t\n\'\"";

	//to interpret
	//"$";

	{
		builtin_error("export", arg, "not a valid identifier");
		return (0);
	}
	if (sep)
	{
		*key = ft_strndup(arg, sep - arg);
		*val = ft_strdup(sep + 1);
		return (1);
	}
	*key = ft_strdup(arg);
	*val = NULL;
	return (1);
}

// redirection des builtins a voir 
int	ft_export(char **arg, t_list *env) 
{
	char	*key;
	char	*val;
	int		i;
	
	i = 0;
	if (!arg[1])
		print_export(env);
	while (arg[++i])
	{
		if (get_key_val(arg[i], &key, &val))
			list_replace(env, key, val);
	}
	return (0);
}
