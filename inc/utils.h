/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:45:15 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/31 16:40:36 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "structs.h"

char	**env_make(t_list *env);
int		env_rebuild(t_data *data);
//env.c

void	print_error(char *builtin, char *arg, char *msg);
int		errors(int ret, char *arg, char *errmsg, int signum);
int		parse_grp_cmd_free(t_list *argv, t_cmd_info *cmd_info, int mode);
int		e_heredoc(const char *m, char *file, char *size, int fd);
//error_handler.c

int		get_fd_in(t_cmd_info *cmd_info);
int		get_fd_out(t_cmd_info *cmd_info);
int		fd_set_val(t_fd *fd, t_elem *e_cmd, t_group *cmds);
//fd_utils.c

char	filetype(const char *path);
//filetype.c

char	*ft_str_concat(const char *s1, char c, const char *s2, char use_c);
//ft_str_concat.c

int		ft_str_split(const char *s, const char *sep, char **dst1, char **dst2);
int		ft_str_contains(const char *s, const char c);
//ft_str_split.c

void	env_set_pwd(t_list *env);
void	env_set_shlvl(t_list *env);
void	env_set__(char **argv, t_list *env);
void	env_set(char const **argv, t_list *env);
//handle_env.c

void	handler_signal(int signum);
void	handler_heredoc(int signum);
void	handler_executor(int signum);
//signal.c

#endif
