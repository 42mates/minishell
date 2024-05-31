/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:46 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 16:35:23 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "structs.h"

int			common(t_group *cmds, t_data *data);
int			common_exe(t_elem *e_cmd, t_data *data, t_fd *fd, int mode);
//common.c

pid_t		executor(t_group *cmds, t_data *data);
int			get_builtins_num(t_elem *e_cmd, t_data *data);
//executor.c

t_group		*group_new(int type);
void		group_free(void *grp);
//group.c

int			parse_manage_heredoc(t_group *cmds);
//heredoc.c

int			parser(t_data *data, t_list *toks);
//parser.c

int			handle_parenthesis(t_elem **e_elem, t_cmd_info *cmd_info);
int			handle_redirect_in(t_elem **e_elem, t_cmd_info *cmd_info);
int			handle_redirect_out(t_elem **e_elem, t_cmd_info *cmd_info);
//parser_handle_tokens.c

int			parse_collect_chunks(
				char *s, t_data *data, t_list *chunks, int *size);
//parser_dollar.c

int			parse_groups(t_list *grps, t_elem *e_tok, long type, long level);
int			parse_is_or_and_valid(t_list *grps);
//parser_groups.c

pid_t		parse_manage_group(long type, t_list *grp, t_data *data);
int			parse_grp_cmd(t_elem *e_elem, t_list *cmds);
//parser_manage_group.c

void		*free_str_array(char **array, int a);
t_list		*parse_star(const char *word);
//parser_star.c

int			parse_token_field(
				t_list *str, t_data *data, char **word, t_elem_info *info);
//parser_token_field.c

int			parse_token(t_elem **e_elem, t_list *extra, t_data *data, long k);
//parser_token.c

int			is_extra(void *key);
int			parse_alloc_c_info(t_chunk_info **c_info, int start, int end);
t_cmd_info	*cmd_info_init(void);
void		parse_init_fpack(
				t_field_pack *f_pack, t_chunk_info *c_info, int *i, int *size);
//parser_utils.c

int			get_fd_in(t_cmd_info *cmd_info);
int			get_fd_out(t_cmd_info *cmd_info);
int			pipes(t_group *cmds, t_data *data);
//pipes.c

int			subshell(t_group *cmds, t_data *data);
int			subshell_exe(t_elem *e_cmd, t_data*data, t_fd *fd);
int			redir_fd(int in, int out);
//subshell.c

#endif
