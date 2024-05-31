/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:13:17 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	errors(int ret, char *arg, char *errmsg, int signum)
{
	print_error(NULL, arg, errmsg);
	g_signal = signum;
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
	if (mode == 1 || mode == 2)
		return (1);
	else if (mode == 3)
		return (errors(1, NULL, "Error: parse_grp_cmd_free", 1));
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
		return (errors(1, NULL, (char *)m, 1));
	return (0);
}

/**
 * Prints an error message for a specific builtin command.
 *
 * @param builtin The name of the builtin command, or NULL if N/A.
 * @param arg The argument associated with the error, or NULL if N/A.
 * @param msg The error message to be displayed.
 */
void	print_error(char *builtin, char *arg, char *msg)
{
	int	is_export;

	is_export = !ft_strcmp(builtin, "export");
	if (ft_strncmp(arg, "debug: ", 7))
		write(2, "msh: ", 5);
	if (builtin)
	{
		write(2, builtin, ft_strlen(builtin));
		write(2, ": ", 2);
	}
	if (arg)
	{
		if (is_export)
			write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		if (is_export)
			write(2, "'", 1);
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
