/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:44:14 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/29 16:55:55 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_var(t_elem *node, char *prefix)
{
	char	*special;

	special = ft_strchrset(node->val, " \t\n\"\\$");
	write(1, prefix, ft_strlen(prefix));
	write(1, node->key, ft_strlen(node->key));
	if (node->val)
	{
		write(1, "=\"", 2);
		write(1, node->val, ft_strlen(node->val));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}
