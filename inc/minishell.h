/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:17:30 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/31 16:35:34 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <fcntl.h>

# include "../libft/libft.h"

# include "builtins.h"
# include "defines.h"
# include "lexer.h"
# include "parser.h"
# include "structs.h"
# include "utils.h"

extern pid_t			g_signal;

#endif
