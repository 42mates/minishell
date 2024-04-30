/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:39:44 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/24 17:35:52 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void	get_key_and_val(char *line, char **key, char **val)
{
	int	sep;

	sep = 0;
	while (line[sep] != '=' && line[sep])
		sep++;
	*key = ft_strndup(line, sep);
	*val = ft_strdup(line + sep + 1);
}

/**
 * Converts a null-terminated array of strings into a linked list.
 *
 * @param tab The null-terminated array of strings to convert.
 * @return A pointer to the newly created linked list,
 * or NULL if an error occurred.
 */
t_list	*tab_to_list(char **tab)
{
	t_list	*res;
	char	*key;
	char	*val;
	int		i;

	res = list_new((t_cmp_key)ft_strcmp, free, free);
	if (!res)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		get_key_and_val(tab[i], &key, &val);
		list_put(res, key, val);
	}
	return (res);
}
