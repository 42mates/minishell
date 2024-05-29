/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aleksei.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:14:38 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/29 16:18:51 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALEKSEI_H
# define ALEKSEI_H

# include "lexer.h"
# include "parser.h"
# include "../minishell.h"

# define ERROR_PIPE				"syntax error near unexpected token `|'"
# define ERROR_AND				"syntax error near unexpected token `&&'"
# define ERROR_OR				"syntax error near unexpected token `||'"
# define ERROR_PARENTHESIS		"syntax error near unexpected token `(' or `)'"
# define ERROR_NEW_LINE			"syntax error near unexpected token `newline'"

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

int			ft_str_split(
				const char *s, const char *sep, char **dst1, char **dst2);
int			ft_str_contains(const char *s, const char c);

int			get_fd_in(t_cmd_info *cmd_info);
int			get_fd_out(t_cmd_info *cmd_info);
int			fd_set_val(t_fd *fd, t_elem *e_cmd, t_group *cmds);

// signal.c
void		handler_signal(int signum);
void		handler_heredoc(int signum);
void		handler_executor(int signum);

// error_handler.c
int			errors(int ret, char *arg, char *errmsg, int signum);
int			parse_grp_cmd_free(t_list *argv, t_cmd_info *cmd_info, int mode);
int			e_heredoc(const char *m, char *file, char *size, int fd);

char		filetype(const char *path);
// lexer.c

// parser.c
int			parser(t_data *data, t_list *toks);

int			handle_parenthesis(t_elem **e_elem, t_cmd_info *cmd_info);
int			handle_redirect_in(t_elem **e_elem, t_cmd_info *cmd_info);
int			handle_redirect_out(t_elem **e_elem, t_cmd_info *cmd_info);

// parser_manage_group.c
pid_t		parse_manage_group(long type, t_list *grp, t_data *data);
int			parse_grp_cmd(t_elem *e_elem, t_list *cmds);

// parser_dollar.c
int			parse_collect_chunks(
				char *s, t_data *data, t_list *chunks, int *size);

// parser_groups.c
int			parse_groups(t_list *grps, t_elem *e_tok, long type, long level);
int			parse_is_or_and_valid(t_list *grps);

// parser_token_field.c 
int			parse_token_field(
				t_list *str, t_data *data, char **word, t_elem_info *info);

// parser_token.c
int			parse_token(t_elem **e_elem, t_list *extra, t_data *data, long k);

// parser_utils.c
int			is_extra(void *key);
int			parse_alloc_c_info(t_chunk_info **c_info, int start, int end);
t_cmd_info	*cmd_info_init(void);
void		parse_init_fpack(
				t_field_pack *f_pack, t_chunk_info *c_info, int *i, int *size);

// heredoc.c
int			parse_manage_heredoc(t_group *cmds);
char		*ft_str_concat(const char *s1, char c, const char *s2, char use_c);

// parser_star.c
void		*free_str_array(char **array, int a);
t_list		*parse_star(const char *word);

// group.c
t_group		*group_new(int type);
void		group_free(void *grp);

// pipes.c
int			get_fd_in(t_cmd_info *cmd_info);
int			get_fd_out(t_cmd_info *cmd_info);
int			pipes(t_group *cmds, t_data *data);

// executor.c
pid_t		executor(t_group *cmds, t_data *data);
int			get_builtins_num(t_elem *e_cmd, t_data *data);

char		*set_current_path(char *str);
char		*set_parent_path(char *str);
char		*set_home_path(char *str, t_list *env_lst);
char		*set_path(char *str, t_list *env_lst);
// set_path.c

// subshell.c
int			subshell(t_group *cmds, t_data *data);
int			subshell_exe(t_elem *e_cmd, t_data*data, t_fd *fd);
int			redir_fd(int in, int out);

// common.c
int			common(t_group *cmds, t_data *data);
int			common_exe(t_elem *e_cmd, t_data *data, t_fd *fd, int mode);

// env.c
char		**env_make(t_list *env);
int			env_rebuild(t_data *data);

// command_call.c
int			command_call(t_elem *e_cmd, t_data *data, t_fd *fd);

// builtins_call.c
int			builtins_exe(int i, t_elem *e_cmd, t_data *data, t_fd *fd);
int			builtins_call(int i, t_elem *e_cmd, t_data *data, t_fd *fd);

#endif