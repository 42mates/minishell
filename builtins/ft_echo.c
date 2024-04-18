/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:41:45 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/17 12:26:30 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Reproduce the behavior of the echo command, with the `-n` option..
 *
 * @param args The NULL-terminated arguments to be written to the 
 * standard output.
 */
int	ft_echo(char **args)
{
	int		i;
	int		newline;
	char	*str;
	
	if (!args[1])
		return (write(1, "\n", 1), 0);
	newline = ft_strcmp(args[1], "-n");
	i = 0;
	if (!newline)
		i++;
	while (args[++i])
	{
		str = args[i];
		write(STDOUT_FILENO, str, ft_strlen(str));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
