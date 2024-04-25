/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:14:38 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 12:40:24 by akurochk         ###   ########.fr       */
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

# include <stdio.h>      // for printf
# include <stdlib.h>     // for malloc, free, exit, getenv
# include <unistd.h>     // for write, access, open, read, close,
//							fork, getcwd, chdir, dup, dup2, pipe, execve
# include <sys/wait.h>   // for wait, waitpid, wait3, wait4
# include <signal.h>     // for signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>   // for stat, lstat, fstat
# include <dirent.h>     // for opendir, readdir, closedir
# include <string.h>     // for strerror
# include <errno.h>      // for perror
# include <termios.h>    // for tcsetattr, tcgetattr
// for readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history
# include <readline/readline.h> 
# include <sys/ioctl.h>  // for ioctl
//# include <ttyname.h>    // for isatty, ttyname, ttyslot
# include <linux/limits.h>
# include <readline/history.h>
# include <sys/types.h>
# include <fcntl.h>
# include "list.h"
# include "lexer.h"
# include "parser.h"

# define PROMT "$> " // what we must use as a promt?

extern pid_t			g_signal;

typedef struct s_data	t_data;

/* 
typedef for ptr to builtin function
example: int ft_echo(t_data *data, t_list *cmd)
*/
typedef int				(*t_builtin)(t_data *, t_list *);

/*
builtins and f_builtins to connect commands with functions
and skip if-else constructions
*/
typedef struct s_data
{
	char		flag_exit;
	char		flag_env;
	char		**env;
	t_list		*env_lst;
	char		*builtins[7];
	t_builtin	f_builtins[7];
	char		*g_signal_str;
}	t_data;

typedef struct s_elem_info
{
	int	size;
	int	flag;
}	t_elem_info;

typedef struct s_chunk_info
{
	int	start;
	int	end;
}	t_chunk_info;

typedef struct s_cmd_info
{
	int		level;
	int		flag;
	char	*f_in;
	char	*f_out;
	char	*sep;
}	t_cmd_info;

typedef struct s_field_pack
{
	int				*i;
	int				*size;
	t_chunk_info	*c_info;
}	t_field_pack;

typedef struct s_group
{
	int			type;
	t_list		*cmds;
	t_list		*files;
}	t_group;

typedef struct s_fd
{
	int		fds[2];
	int		pfd[2];
}	t_fd;

int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	**ft_split(char const *s, char c);

// signal.c
void	handler_signal(int signum);
void	handler_heredoc(int signum);
void	handler_executor(int signum);

// error_handler.c
int		errors(int ret, const char *m, char mode, int signum);
int		parse_grp_cmd_free(t_list *argv, t_cmd_info *cmd_info, int mode);
int		e_heredoc(const char *m, char *file, char *size, int fd);

// ft_substr.c
char	*ft_substr(char const *s, unsigned int start, size_t len);

// parser.c
int		parser(t_data *data, t_list *toks);

// heredoc.c
int		parse_manage_heredoc(t_group *cmds);
char	*ft_str_concat(const char *s1, char c, const char *s2, char use_c);


// parser_star.c
void	*free_str_array(char **array, int a);
t_list	*parse_star(const char *word);

// group.c
t_group	*group_new(int type);
void	group_free(void *grp);

// pipes.c
int		get_fd_in(t_cmd_info *cmd_info);
int		get_fd_out(t_cmd_info *cmd_info);
int		pipes(t_group *cmds, t_data *data);

// executor.c
pid_t	executor(t_group *cmds, t_data *data);
int		get_builtins_num(t_elem *e_cmd, t_data *data);

// subshell.c
int		subshell(t_group *cmds, t_data *data);
int		subshell_exe(t_elem *e_cmd, t_data*data, t_fd *fd);
int		redir_fd(int in, int out);

// common.c
int		common(t_group *cmds, t_data *data);
int		common_exe(t_elem *e_cmd, t_data *data, t_fd *fd, int mode);

// env.c
char	**env_make(t_list *env);
int		env_rebuild(t_data *data);

// command_call.c
int		command_call(t_elem *e_cmd, t_data *data, t_fd *fd);

// builtins_call.c
int		builtins_exe(int i, t_elem *e_cmd, t_data *data, t_fd *fd);
int		builtins_call(int i, t_elem *e_cmd, t_data *data, t_fd *fd);

//TEST
void	test_print_tokens(t_list *toks);
void	test_print_env(t_list *env);

#endif