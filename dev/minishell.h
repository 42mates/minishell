/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:14:38 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/15 20:25:50 by akurochk         ###   ########.fr       */
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

# define PROMT "$> "

/* 
template for funtions for linked list
*/
typedef int				(*t_cmp_key)(const void	*key_1, const void *key_2);
typedef void			(*t_dst_key)(void	*key);
typedef void			(*t_dst_con)(void	*content);

/*
element of linked list
*/
typedef struct s_elem
{
	void			*key;
	void			*content;
	struct s_list	*next;
}	t_elem;

typedef struct s_list
{
	t_elem		*head;
	t_cmp_key	cmp_key;
	t_dst_key	dst_key;
	t_dst_con	dst_con;
}	t_list;


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