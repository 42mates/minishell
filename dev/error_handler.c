/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:13:17 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 12:09:10 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
ret		- return val of function.
m		- error message.
mode	- 1 to use perror() and set g_signal=1.
signum	- signal number.
*/
int	errors(int ret, const char *m, char mode, int signum)
{
	if (m && *m && !mode)
	{
		write(STDERR_FILENO, m, ft_strlen(m));
		write(STDERR_FILENO, "\n", 1);
		// (void)signum; // mockup
		g_signal = signum;
		return (ret);
	}
	if (errno != 0 && mode)
	{
		if (m && *m)
			perror(m);
		else
			perror("Error: ");
		g_signal = 1;
	}
	else if (errno != 0)
		perror("Oh, it's an EPIC error.. ");
	return (ret);
}

/*
Frees args, cmd_info.
Prints error in mode 2 and 3.
Reurns 0 if just use frees.
*/
int	parse_grp_cmd_free(t_list *argv, t_cmd_info *cmd_info, int mode)
{
	list_free(argv);
	free(cmd_info);
	if (mode == 1)
		return (1);
	else if (mode == 2)
		return (errors(1, "Error: syntax error", 0, 258));
	else if (mode == 3)
		return (errors(1, "Error: parse_grp_cmd", 1, 0));
	return (0);
}

/*
Frees file, size, close fd.
Prints error if has message and returns 1.
Returns 0 if no message.
*/
int	e_heredoc(const char *m, char *file, char *size, int fd)
{
	if (m && file)
		free(file);
	if (size)
		free(size);
	if (fd != -1)
		close(fd);
	if (m)
		return (errors(1, m, 1, 0));
	return (0);
}
