/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hendler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:13:17 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/16 20:42:31 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
ret		- return val of function.
m		- error message.
mode	- 1 to use perror() and SIGHUP signal.
signum	- signal number.
*/
int	error_handler(int ret, char *m, char mode, int signum)
{
	if (m && *m && !mode)
	{
		write(STDERR_FILENO, m, ft_strlen(m));
		write(STDERR_FILENO, "\n", 1);
		g_signal = signum;
		return (ret);
	}
	if (errno != 0 && mode)
	{
		if (m && *m)
			perror(m);
		else
			perror("Error minishell: ");
		g_signal = SIGHUP;
	}
	else if (errno != 0)
		perror("Oh, it's an EPIC error.. ");
	return (ret);
}
