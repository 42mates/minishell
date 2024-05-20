/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:49:20 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/20 16:53:20 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Determines the type of a file or directory based on its path.
 *
 * @param path The path of the file or directory.
 * @return The file type as a character:
 *         '-' for regular file,
 *         'd' for directory,
 *         'c' for character device,
 *         'b' for block device,
 *         'p' for named pipe (FIFO),
 *         'l' for symbolic link,
 *         's' for socket,
 *         0 if the file type cannot be determined or an error occurs.
 */
char	filetype(const char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (0);
	if (S_ISREG(buf.st_mode))
		return ('-');
	if (S_ISDIR(buf.st_mode))
		return ('d');
	if (S_ISCHR(buf.st_mode))
		return ('c');
	if (S_ISBLK(buf.st_mode))
		return ('b');
	if (S_ISFIFO(buf.st_mode))
		return ('p');
	if (S_ISLNK(buf.st_mode))
		return ('l');
	if (S_ISSOCK(buf.st_mode))
		return ('s');
	return (0);
}
