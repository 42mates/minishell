/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/29 17:31:59 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "parser.h"

/*---PARSE RUN GROUP---*/

int	is_extra(void *key)
{
	return ((long)key == L_WORD
		|| (long)key == L_S_QUOT
		|| (long)key == L_D_QUOT);
}

/*
Returns 0 if OK.
Returns 1 if can't create element in extra.
*/
int	parse_sub_token(t_elem *e_elem, t_list *extra)
{
	if (is_extra(e_elem->key))
		return (!list_put(extra, e_elem->key, ft_strdup((char *)e_elem->val)));
	return (!list_put(extra, e_elem->key, e_elem->val));
}

void	parse_token_first_loop(t_list **str, t_elem **e_elem)
{
	*str = list_new(cmp_int, NULL, NULL);
	list_put(*str, (*e_elem)->key, (*e_elem)->val);
	while ((*e_elem)->next && is_extra(((t_elem *)(*e_elem)->next)->key))
	{
		(*e_elem) = (*e_elem)->next;
		list_put(*str, (*e_elem)->key, (*e_elem)->val);
	}
}

void	parse_token_second_loop(t_list *extra, char *word, t_list *words)
{
	t_elem	*e_word;

	free(word);
	e_word = words->head;
	while (e_word != NULL)
	{
		list_put(extra, (void *)L_WORD, e_word->val);
		if (e_word->next)
			list_put(extra, (void *)L_SPACE, NULL);
		e_word = e_word->next;
	}
	list_free(words);
}

void parse_token_field_free(t_list *chunks, char **word)
{
	if (chunks)
		list_free(chunks);
	if (*word)
		free(*word);
}

int	parse_alloc_c_info(t_chunk_info **c_info, int start, int end)
{
	*c_info = (t_chunk_info *)malloc(sizeof(t_chunk_info));
	if (*c_info == NULL)
		return (errors(1, "Error: parse_alloc_c_info", 1, 0));
	(*c_info)->start = start;
	(*c_info)->end = end;
	return (0);
}

void	parse_init_fpack(t_field_pack *f_pack, t_chunk_info *c_info,
	int *i, int *size)
{
	f_pack->i = i;
	f_pack->size = size;
	f_pack->c_info = c_info;
}


int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int update_g_signal_str(t_data *data)
{
	free(data->g_signal_str);
	data->g_signal_str = ft_itoa(g_signal);
	if (!data->g_signal_str)
		return (errors(1, "Error: update_g_signal_str", 1, 0));
	return (0);
}

int	get_var(const char *s, t_data *data, char **ptr_env, int *pos)
{
	int		i;
	char	*var_name;

	i = 0;
	if (s[i] == '\0')
	{
		ptr_env = NULL;
		return (0);
	}
	if (s[i] == '?')
	{
		if (update_g_signal_str(data))
			return (1);
		*ptr_env = data->g_signal_str;
		*pos = *pos + 1;
		return (0);
	}
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (i == 0)
	{
		ptr_env = NULL;
		return (0);
	}
	var_name = ft_substr(s, 0, i);
	if (!var_name)
		return (errors(1, "Error: get_var", 1, 0));
	ptr_env = list_get(data->env_lst, var_name);
	*pos = *pos + i;
	free(var_name);
	return (0);
}

int	parse_colect_from_env(char *s, t_data *data,
	t_list *chunks, t_field_pack *f_pack)
{
	char	*ptr_env;

	if (get_var(s + *(f_pack->i) + 1, data, &ptr_env, f_pack->i))
		return (1);
	if (!ptr_env && s[*(f_pack->i)] == '$')
		*(f_pack->size) += (++(f_pack->c_info->end) || 1);
	if (ptr_env)
	{
		if (parse_alloc_c_info(&(f_pack->c_info), 0, ft_strlen(ptr_env)))
			return (1);
		if (!list_put(chunks, f_pack->c_info, ptr_env))
		{
			free(f_pack->c_info);
			return (errors(1, "Error: parse_colect_from_env", 1, 0));
		}
		*(f_pack->size) += f_pack->c_info->end;
	}
	++(*(f_pack->i));
	return (0);
}

int 	parse_collect_chunks(char *s, t_data *data, t_list *chunks, int *size)
{
	int				i;
	int				j;
	t_chunk_info	*c_info;
	t_field_pack	f_pack;

	i = 0;
	j = 0;
	c_info = NULL;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
		{
			(*size)++;
			i++;
		}
		if (parse_alloc_c_info(&c_info, j, i))
			return (1);
		if (!list_put(chunks, c_info, s))
		{
			free(c_info);
			return (errors(1, "Error: parse_collect_chunks", 1, 0));
		}
		parse_init_fpack(&f_pack, c_info, &i, size);
		if (s[i] == '$' && parse_colect_from_env(s, data, chunks, &f_pack))
			return (1);
		j = i;
	}
	return (0);
}

int	parse_token_field_pre(t_list *str, t_data *data, t_list *chunks,
	t_elem_info *e_info)
{
	t_elem			*e_elem;
	t_chunk_info	*c_info;

	c_info = NULL;
	e_elem = str->head;
	while (e_elem)
	{

		if ((long)e_elem->key == L_S_QUOT || e_info->flag)
		{
			if (parse_alloc_c_info(&c_info, 0, ft_strlen((char *)e_elem->val)))
				return (1);
			e_info->size = e_info->size + c_info->end;
			if (!list_put(chunks, c_info, e_elem->val))
			{
				free (c_info);
				return (errors(1, "Error: parse_token_field_pre", 1, 0));
			}
		}
		else if (parse_collect_chunks((char *)e_elem->val,	data, chunks, &(e_info->size)))
			return (1);
		e_elem = e_elem->next;

	}
	e_info->flag = 0;
	return (0);
}

int	parse_token_field_cpy(t_list *chunks, char *word)
{
	int		i;
	int		j;
	t_elem	*e_elem;

	i = 0;
	e_elem = chunks->head;
	while (e_elem != NULL)
	{
		j = ((t_chunk_info *)e_elem->key)->start;
		while (j < ((t_chunk_info *)e_elem->key)->end)
			word[i++] = ((char *)e_elem->val)[j++];
		e_elem = e_elem->next;
	}
	return (0);
}

void	parse_token_field_free_var(t_list *str, char **word, t_elem_info *info)
{
	t_elem	*e_elem;

	if (info->size != 0)
		return ;
	e_elem = str->head;
	while (e_elem)
	{
		if ((long)e_elem->key != L_WORD)
			return ;
		e_elem = e_elem->next;
	}
	free(*word);
	*word = NULL;
}

int	parse_token_field(t_list *str, t_data *data, char **word, t_elem_info *info)
{
	t_list	*chunks;

	chunks = list_new(NULL, free, NULL);
	if (chunks == NULL)
		return (errors(1, "Error: parse_token_field", 1, 0));
	*word = NULL;
	info->size = 0;
	if (parse_token_field_pre(str, data, chunks, info))
		return (parse_token_field_free(chunks, word), 1);
	*word = (char *)malloc(sizeof(char) * (info->size + 1));
	if (*word == NULL)
		return (parse_token_field_free(chunks, word), 1);
	(*word)[info->size] = '\0';
	if (parse_token_field_cpy(chunks, *word))
		return (parse_token_field_free(chunks, word), 1);
	parse_token_field_free_var(str, word, info);
	list_free(chunks);
	return (0);
}

int	parse_token(t_elem **e_elem, t_list *extra, t_data *data)
{
	static t_elem_info	info;
	char				*word;
	t_list				*words;
	t_list				*str;

	if ((long)(*e_elem)->key == L_RE_APP)
		info.flag = 1;
	if (is_extra((*e_elem)->key))
	{
		parse_token_first_loop(&str, e_elem);
		if (parse_token_field(str, data, &word, &info) == 1)
			return (list_free(str), 1);
		if (word == NULL)
			return (list_free(str), 0);
		words = parse_star(word);
		if (words == NULL)
			list_put(extra, (void *)L_WORD, word);
		else
			parse_token_second_loop(extra, word, words);
		list_free(str);
	}
	else
		list_put(extra, (*e_elem)->key, NULL);
	return (0);
}

t_list	*parse_extra(t_list *grp, t_data *data)
{
	int		level;
	t_list	*extra;
	t_elem	*e_elem;

	level = 0;
	extra = list_new(cmp_int, NULL, free);
	e_elem = grp->head;
	while (extra != NULL && e_elem != NULL)
	{
		level += ((long)(e_elem->key) == L_PAR_L)
			+ ((long)(e_elem->key) == L_PAR_R) * (-1);
		if (level > 0 && parse_sub_token(e_elem, extra))
			return (list_free(extra), NULL);
		else if (level == 0 && parse_token(&e_elem, extra, data))
			return (list_free(extra), NULL);
		e_elem = e_elem->next;
	}
	return (extra);
}

t_cmd_info	*cmd_info_init(void)
{
	t_cmd_info	*ret;

	ret = malloc(sizeof(t_cmd_info));
	if (ret == NULL)
		return (NULL);
	ret->level = 0;
	ret->flag = 0;
	ret->f_in = NULL;
	ret->f_out = NULL;
	ret->sep = NULL;
	return (ret);
}

/*
Returns next token != L_SPACE.
Or returns NULL.
*/
t_elem	*parse_get_next_nonspace_token(t_elem *e_elem)
{
	if (!e_elem)
		return (NULL);
	e_elem = e_elem->next;
	while (e_elem && (long)e_elem->key == L_SPACE)
		e_elem = e_elem->next;
	return (e_elem);
}

/*
Returns 0 is OK.
*/
int	parse_manage_token2(t_elem **e_elem, t_cmd_info *cmd_info)
{
	if ((long)(*e_elem)->key == L_RE_IN || (long)(*e_elem)->key == L_RE_DOC)
	{
		if ((long)(*e_elem)->key == L_RE_DOC)
			cmd_info->flag |= CMD_INS;
		else
			cmd_info->flag &= ~CMD_INS;
		*e_elem = parse_get_next_nonspace_token(*e_elem);
		if (*e_elem == NULL || (long)(*e_elem)->key != L_WORD)
			return (errors(1, "Error: parse error near '<' or '<<'", 0, 258));
		cmd_info->f_in = (*e_elem)->val;
		return (0);
	}
	if ((long)(*e_elem)->key == L_RE_OUT || (long)(*e_elem)->key == L_RE_APP)
	{
		if ((long)(*e_elem)->key == L_RE_APP)
			cmd_info->flag |= CMD_APP;
		else
			cmd_info->flag &= ~CMD_APP;
		*e_elem = parse_get_next_nonspace_token(*e_elem);
		if (*e_elem == NULL || (long)(*e_elem)->key != L_WORD)
			return (errors(1, "Error: parse error near '>' or '>>'", 0, 258));
		cmd_info->f_in = (*e_elem)->val;
		return (0);
	}
	return (0);
}

/*
Returns 0 is OK.
*/
int	parse_manage_token(t_elem **e_elem, t_cmd_info *cmd_info, t_list *argv)
{
	if (*e_elem == NULL)
		return (errors(1, "Error: someting goes REALLY wrong", 0, 777));
	if ((long)(*e_elem)->key == L_PAR_L || (long)(*e_elem)->key == L_PAR_R)
	{
		cmd_info->level += ((long)(*e_elem)->key == L_PAR_L)
			+ (-1) * ((long)(*e_elem)->key == L_PAR_R);
		cmd_info->flag |= CMD_SUB;
		if ((cmd_info->level == 1 && (long)(*e_elem)->key == L_PAR_L)
			|| (cmd_info->level == 0 && (long)(*e_elem)->key == L_PAR_R))
			return (0);
	}
	if ((long)(*e_elem)->key == L_SPACE && cmd_info->level == 0)
		return (0);
	if ((cmd_info->flag & CMD_SUB)
		&& cmd_info->level == 0 && (long)(*e_elem)->key == L_WORD)
		return (errors(1, "Error: parse_manage_token: extra token", 0, 258));
	if (((long)(*e_elem)->key == L_WORD || cmd_info->level > 0)
		&& !list_put(argv, (*e_elem)->key, (*e_elem)->val))
		return (errors(1, "Error: parse_manage_token", 1, 0));
	if (cmd_info->level > 0)
		return (0);
	return (parse_manage_token2(e_elem, cmd_info));
}

int	parse_grp_cmd(t_elem *e_elem, t_list *cmds)
{
	t_list		*argv;
	t_cmd_info	*cmd_info;

	cmd_info = cmd_info_init();
	if (cmd_info == NULL)
		return (errors(1, "Error: parse_grp_cmd: cmd_info_init", 1, 0));
	argv = list_new(NULL, NULL, NULL);
	if (argv == NULL)
		return (free(cmd_info),
			errors(1, "Error: parse_grp_cmd: list_new", 1, 0));
	while (e_elem != NULL && ((long)e_elem->key != L_PIPE || cmd_info->level))
	{
		if (parse_manage_token(&e_elem, cmd_info, argv))
			return (parse_grp_cmd_free(argv, cmd_info, 1));
		e_elem = e_elem->next;
	}
	if (!list_size(argv) && cmd_info->f_out == NULL && cmd_info->f_in == NULL)
		return (parse_grp_cmd_free(argv, cmd_info, 2));
	if (e_elem == NULL || (long)e_elem->key == L_PIPE)
	{
		if (!list_put(cmds, argv, cmd_info))
			return (parse_grp_cmd_free(argv, cmd_info, 3));
		return (0);
	}
	return (parse_grp_cmd_free(argv, cmd_info, 1));
}


int	parse_grp_pipe (t_list *extra, t_list *cmds)
{
	t_elem	*e_elem;

	e_elem = extra->head;
	while (e_elem != NULL)
	{
		if (parse_grp_cmd(e_elem, cmds))
			return (1);
		while (e_elem != NULL && (long)e_elem->key != L_PIPE)
			e_elem = e_elem->next;
		if (e_elem != NULL && e_elem->next == NULL)
			return (errors(1, "Error: parse error near '|'", 0, 258));
		if (e_elem != NULL)
			e_elem = e_elem->next;
	}
	return (0);
}

/*
Retrns 0 if OK.
*/
int	parse_prepare_grp(t_list *extra, t_group *cmds)
{
	if (cmds->type & PARSER_PIPE)
		return (parse_grp_pipe(extra, cmds->cmds));
	return (parse_grp_cmd(extra->head, cmds->cmds));
}

/*
Returns pid value if OK.
Returns -1 if fail.
*/
pid_t	parse_manage_group(long type, t_list *grp, t_data *data)
{
	pid_t	pid;
	t_list	*extra;
	t_group	*cmds;

	pid = -1;
	extra = parse_extra(grp, data);
	if (extra)
	{
		cmds = group_new(type);
		if (!cmds)
			return (-1);
		if (parse_prepare_grp(extra, cmds))
			return (group_free(cmds), list_free(extra), -1);
		if (parse_manage_heredoc(cmds))
			return (group_free(cmds), list_free(extra), -1);
		pid = executor(cmds, data);
		group_free(cmds);
		list_free(extra);
	}
	return (pid);
}

/*---PARSE WAIT ALL---*/

void	parse_wait_all(int pid, int *status)
{
	int	child;

	child = 1;
	while (child > 0)
	{
		child = waitpid(0, status, 0);
		if (pid == child)
		{
			g_signal = WEXITSTATUS(*status);
			if (WIFSIGNALED(*status))  // 0 if was stopped by signal
			{
				g_signal = WTERMSIG(*status);
				if (g_signal != 131)
					g_signal += 128;
			}
		}
	}
}

/*---PARSE RUN CHAIN---*/

int	parse_check_chain(t_elem *e_elem, int *chain)
{
	if ((g_signal == 0 && ((long)e_elem->key == L_OR))
		|| (g_signal != 0 && ((long)e_elem->key == L_AND)))
		return (1);
	*chain = 0;
	return (0);
}

/*---PARSE GROUPS EXE---*/

/*
Returns 0 if OK.
*/
int	parse_groups_exe(t_list *grps, t_data *data)
{
	int		chain;
	int		status;
	pid_t	pid;
	t_elem	*e_elem;

	chain = 0;
	e_elem = grps->head;
	while (e_elem != NULL)
	{
		if (chain == 0)
		{
			pid = parse_manage_group((long)e_elem->key, e_elem->val, data);
			if (pid < 0)
				return (1);
			if (pid > 0)
				parse_wait_all(pid, &status);
			chain = 1;
		}
		else if (parse_check_chain(e_elem, &chain))
			return (0);
		e_elem = e_elem->next;
	}
	return (0);
}

/*---PARSER---*/

/*
Returns 0 if OK.
*/
int	parser(t_data *data, t_list *toks) /*-OK-*/
{
	t_list	*grps;

	grps = list_new(NULL, NULL, list_free);
	if (grps == NULL)
		return (1);
	if (parse_groups(grps, toks))
		return (list_free(grps), 1);
	if (list_size(grps) == 0)
		return (list_free(grps), 0);
	if (parse_is_or_and_valid(grps))
		return (list_free(grps), 1);
	if (parse_groups_exe(grps, data))
		return (list_free(grps), 1);
	list_free(grps);
	return (0);
}
