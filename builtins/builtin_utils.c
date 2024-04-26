/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:44:14 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/25 18:13:08 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_error(char *builtin, char *arg, char *msg)
{
	int	is_export;

	write(2, PROMPT, ft_strlen(PROMPT) - 2);
	write(2, ": ", 2);
	is_export = !ft_strcmp(builtin, "export");
	write(2, builtin, ft_strlen(builtin));
	write(2, ": ", 2);
	if (is_export)
		write(2, "`", 1);
	write(2, arg, ft_strlen(arg));
	if (is_export)
		write(2, "'", 1);
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

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
