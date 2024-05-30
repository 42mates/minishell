/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_manage_group2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/30 16:59:02 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Parses and manages tokens during the parsing process.
 * This function executes different tasks based on the type of token 
 * encountered, such as handling parentheses, words, spaces, and redirections.
 *
 * @param e_elem   A pointer to the current token element.
 * @param cmd_i    A pointer to the command information structure.
 * @param argv     A pointer to the list of arguments.
 * @return         Returns 0 on success, or an error code on failure.
 */
static int	parse_manage_token(t_elem **e_elem, t_cmd_info *cmd_i, t_list *argv)
{
	if (*e_elem == NULL)
		return (errors(1, "debug: someting goes REALLY wrong", 0, 777));
	if ((long)(*e_elem)->key == L_PAR_L || (long)(*e_elem)->key == L_PAR_R)
	{
		if (!handle_parenthesis(e_elem, cmd_i))
			return (0);
	}
	if ((long)(*e_elem)->key == L_SPACE && cmd_i->level == 0)
		return (0);
	if ((cmd_i->flag & CMD_SUB) && cmd_i->level == 0
		&& (long)(*e_elem)->key == L_WORD)
		return (errors(1, "debug: parse_manage_token", "extra token", 258));
	if (((long)(*e_elem)->key == L_WORD || cmd_i->level > 0)
		&& !list_put(argv, (*e_elem)->key, (*e_elem)->val))
		return (errors(1, "debug: parse_manage_token", "list_put", 0));
	if (cmd_i->level > 0)
		return (0);
	if ((long)(*e_elem)->key == L_RE_IN || (long)(*e_elem)->key == L_RE_DOC)
		return (handle_redirect_in(e_elem, cmd_i));
	if ((long)(*e_elem)->key == L_RE_OUT || (long)(*e_elem)->key == L_RE_APP)
		return (handle_redirect_out(e_elem, cmd_i));
	return (0);
}

/**
 * To help with Norminette
 */
static int	parse_grp_cmd_second(
	t_elem *e_elem, t_list *cmds, t_list *argv, t_cmd_info *cmd_info)
{
	if (!list_size(argv) && cmd_info->f_out == NULL && cmd_info->f_in == NULL)
		return (parse_grp_cmd_free(argv, cmd_info, 2));
	if (!e_elem || (long)e_elem->key == L_PIPE)
	{
		if (!list_put(cmds, argv, cmd_info))
			return (parse_grp_cmd_free(argv, cmd_info, 3));
		return (0);
	}
	return (parse_grp_cmd_free(argv, cmd_info, 1));
}

/**
 * Parses a group command from the given element (token)
 * and adds it to the list of commands.
 * 
 * @param e_elem The element to start parse.
 * @param cmds The list of commands to add the parsed command to.
 * @return 0 if successful, 1 otherwise.
 */
int	parse_grp_cmd(t_elem *e_elem, t_list *cmds)
{
	t_list		*argv;
	t_cmd_info	*cmd_info;

	cmd_info = cmd_info_init();
	if (cmd_info == NULL)
		return (errors(1, "debug: parse_grp_cmd", "cmd_info_init", 0));
	argv = list_new(NULL, NULL, NULL);
	if (argv == NULL)
		return (free(cmd_info), errors(1, "debug: parse_grp_cmd", "argv", 0));
	while (e_elem && ((long)e_elem->key != L_PIPE || cmd_info->level))
	{
		if (parse_manage_token(&e_elem, cmd_info, argv))
		{
			while (e_elem && ((long)e_elem->key != L_PIPE || cmd_info->level))
				e_elem = e_elem->next;
			list_put(cmds, NULL, NULL);
			return (parse_grp_cmd_free(argv, cmd_info, 1));
		}
		e_elem = e_elem->next;
	}
	return (parse_grp_cmd_second(e_elem, cmds, argv, cmd_info));
}
