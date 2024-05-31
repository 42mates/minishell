/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:55:46 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Returns next non-space element after the current element.
 *
 * @param e_elem The current element.
 * @return The next non-space element, or NULL if there are no more elements.
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

/**
 * Handles parenthesis tokens in the parser.
 * Increments or decrements the level of parenthesis in the command info
 * structure. Sets the flag in the command info structure. Returns 0 if
 * the parenthesis level and token match, 1 otherwise.
 *
 * @param e_elem The current element in the token list.
 * @param cmd_info The command info structure.
 * @return 0 if the parenthesis level and token match, 1 otherwise.
 */
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

/**
 * Handles the input redirection for a command.
 *
 * @param e_elem    Pointer to the current element in the grouped token list.
 * @param cmd_info  Pointer to the command information struct.
 * @return          0 if successful, otherwise an error code.
 */
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
		return (errors(1, NULL, ERROR_NEW_LINE, 2));
	cmd_info->f_in = (*e_elem)->val;
	if ((long)curr->key == L_RE_DOC)
		return (0);
	fd = open(cmd_info->f_in, O_RDONLY, 0644);
	if (fd == -1)
		return (errors(1, cmd_info->f_in, "No such file or directory", 1));
	return (close(fd), 0);
}

/**
 * Handles the output redirection for a command.
 *
 * @param e_elem    Pointer to the current element in the grouped token list.
 * @param cmd_info  Pointer to the command information struct.
 * @return          0 if successful, otherwise an error code.
 */
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
		return (errors(1, NULL, ERROR_NEW_LINE, 2));
	cmd_info->f_out = (*e_elem)->val;
	if ((long)curr->key == L_RE_APP)
		fd = open(cmd_info->f_out, O_CREAT | O_WRONLY, 0644);
	else
		fd = open(cmd_info->f_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (errors(1, cmd_info->f_out, "Permission denied", 1));
	return (close(fd), 0);
}
