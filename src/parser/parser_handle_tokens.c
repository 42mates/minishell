/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:55:46 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/28 17:09:35 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Returns next token != L_SPACE.
Or returns NULL.
*/
static t_elem	*parse_get_next_nonspace_token(t_elem *e_elem)
{
	if (!e_elem)
		return (NULL);
	e_elem = e_elem->next;
	while (e_elem && (long)e_elem->key == L_SPACE)
		e_elem = e_elem->next;
	return (e_elem);
}

int	handle_parenthesis(t_elem **e_elem, t_cmd_info *cmd_info)
{
	cmd_info->level += ((long)(*e_elem)->key == L_PAR_L) + (-1)
		* ((long)(*e_elem)->key == L_PAR_R);
	cmd_info->flag |= CMD_SUB;
	if ((cmd_info->level == 1 && (long)(*e_elem)->key == L_PAR_L)
		|| (cmd_info->level == 0 && (long)(*e_elem)->key == L_PAR_R))
		return (0);
	return (1);
}

int	handle_redirect_in(t_elem **e_elem, t_cmd_info *cmd_info)
{
	int		fd;
	t_elem	*curr;

	curr = *e_elem;
	if ((long)(*e_elem)->key == L_RE_DOC)
		cmd_info->flag |= CMD_INS;
	else
		cmd_info->flag &= ~CMD_INS;
	*e_elem = parse_get_next_nonspace_token(*e_elem);
	if (*e_elem == NULL || (long)(*e_elem)->key != L_WORD)
		return (
			errors(1, NULL, ERROR_NEW_LINE, 2));
	cmd_info->f_in = (*e_elem)->val;
	if ((long)curr->key == L_RE_DOC)
		return (0);
	fd = open(cmd_info->f_in, O_RDONLY, 0644);
	if (fd == -1)
		return (errors(1, cmd_info->f_in, "No such file or directory", 1));
	close(fd);
	return (0);
}

int	handle_redirect_out(t_elem **e_elem, t_cmd_info *cmd_info)
{
	int		fd;
	t_elem	*curr;

	curr = *e_elem;
	if ((long)(*e_elem)->key == L_RE_APP)
		cmd_info->flag |= CMD_APP;
	else
		cmd_info->flag &= ~CMD_APP;
	*e_elem = parse_get_next_nonspace_token(*e_elem);
	if (*e_elem == NULL || (long)(*e_elem)->key != L_WORD)
		return (
			errors(1, NULL, ERROR_NEW_LINE, 2));
	cmd_info->f_out = (*e_elem)->val;
	if ((long)curr->key == L_RE_APP)
		fd = open(cmd_info->f_out, O_CREAT | O_WRONLY, 0644);
	else
		fd = open(cmd_info->f_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (errors(1, cmd_info->f_out, "Permission denied", 1));
	close(fd);
	return (0);
}
