/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:14:38 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/16 10:18:29 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tg
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include "list.h"

# define PROMT "$> " // what we must use as a promt?

typedef struct s_data	t_data;

/* 
typedef for ptr to builtin function
example: int ft_echo(t_info *data, t_list *cmd)
*/
typedef int				(*t_builtin)(t_data *, t_list *);

/*
builtins and f_builtins to connect commands with functions
and skip if-else constructions
*/
typedef struct s_data
{
	int			flag_exit;
	char		**env;
	t_list		env_lst;
	char		*builtins[7];
	t_builtin	f_builtins[7];
}	t_data;

int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

#endif