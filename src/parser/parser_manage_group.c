/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_manage_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/16 16:40:59 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*---PARSE RUN GROUP---*/

/*
Returns 0 if OK.
Returns 1 if can't create element in extra.
*/
static int	parse_sub_token(t_elem *e_elem, t_list *extra)
{
	if (is_extra(e_elem->key))
		return (!list_put(extra, e_elem->key, ft_strdup((char *)e_elem->val)));
	return (!list_put(extra, e_elem->key, e_elem->val));
}

static t_list	*parse_extra(t_list *grp, t_data *data)
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

static int	parse_grp_pipe(t_list *extra, t_list *cmds)
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
static int	parse_prepare_grp(t_list *extra, t_group *cmds)
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
