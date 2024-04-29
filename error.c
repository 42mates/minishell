/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:08:38 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/29 11:09:08 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints an error message for a specific builtin command.
 *
 * @param builtin The name of the builtin command, or NULL if N/A.
 * @param arg The argument associated with the error.
 * @param msg The error message to be displayed.
 */
void	print_error(char *builtin, char *arg, char *msg)
{
	int	is_export;
	int	is_builtin;

	is_export = !ft_strcmp(builtin, "export");
	is_builtin = builtin != NULL;
	write(2, "minishell", 9);
	write(2, ": ", 2);
	if (is_builtin)
	{
		write(2, builtin, ft_strlen(builtin));
		write(2, ": ", 2);
	}
	if (is_export)
		write(2, "`", 1);
	write(2, arg, ft_strlen(arg));
	if (is_export)
		write(2, "'", 1);
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
