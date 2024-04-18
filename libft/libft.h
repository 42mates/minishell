/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:42:24 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/18 16:35:29 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# include "macros.h"
// all macros are in macros.h

# include "files/files.h"
// file-handling related functions are in files/

# include "list/list.h"
// linked list-handling related functions are in list/

# include "strings/strings.h"
// string-handling related functions are in str/

# include "tab/tab.h"
// two-dimensional array-handling related functions are in tab/

# include "other/other.h"
// miscellaneous functions are in other/other.h

#endif
