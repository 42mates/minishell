/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_manage_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Parses a group element inside parenthesis and adds it to the extra list. 
 * If the element is a word or text in quotes, its value will be copied
 * with ft_strdup to list of extra.
 * 
 * @param e_elem The group element to parse.
 * @param extra The list to add the parsed element to.
 * @return Returns 0 if successful, 1 otherwise.
 */
static int	parse_sub_token(t_elem *e_elem, t_list *extra)
{
	if (is_extra(e_elem->key))
		return (!list_put(extra, e_elem->key, ft_strdup((char *)e_elem->val)));
	return (!list_put(extra, e_elem->key, e_elem->val));
}

/**
 * Parses the tokens in a group and returns a list of parsed tokens.
 * It checks level of parenthesis, quotes symbols (dots, stars, etc.)
 * and recombinates the groupped tokens into the list "extra". 
 * 
 * @param grp The list of tokens in the group.
 * @param data The data structure containing additional information.
 * @return A list of recombined tokens, or NULL if an error occurs.
 */
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
		else if (!level && parse_token(&e_elem, extra, data, (long)e_elem->key))
			return (list_free(extra), NULL);
		e_elem = e_elem->next;
	}
	return (extra);
}

/**
 * Parses a group of commands separated by pipes.
 * 
 * @param extra A pointer to list associated with the group.
 * @param cmds A pointer to the group of commands to be parsed and prepared.
 * @return Returns 0 if successful, 1 otherwise.
 */
static int	parse_grp_pipe(t_list *extra, t_list *cmds)
{
	t_elem	*e_elem;

	e_elem = extra->head;
	while (e_elem != NULL)
	{
		if (parse_grp_cmd(e_elem, cmds) && e_elem == NULL)
			return (1);
		while (e_elem != NULL && (long)e_elem->key != L_PIPE)
			e_elem = e_elem->next;
		if (e_elem != NULL && e_elem->next == NULL)
			return (errors(1, NULL, ERROR_PIPE, 258));
		if (e_elem != NULL)
			e_elem = e_elem->next;
	}
	return (0);
}

/**
 * Parses and prepares a group of commands.
 * 
 * This function is responsible for choosing parsing way and preparing a group
 * of commands. If the group contains a pipe, it calls the parse_grp_pipe()
 * to handle it. Otherwise, it calls the parse_grp_cmd() to parse the commands.
 * 
 * @param extra A pointer to list associated with the group.
 * @param cmds A pointer to the group of commands to be parsed and prepared.
 * @return Returns 0 if successful, 1 otherwise.
 */
static int	parse_prepare_grp(t_list *extra, t_group *cmds)
{
	if (cmds->type & PARSER_PIPE)
		return (parse_grp_pipe(extra, cmds->cmds));
	return (parse_grp_cmd(extra->head, cmds->cmds));
}

/**
 * Handles and execute a group of commands.
 *
 * @param type The type of the group.
 * @param grp The list of tokens in the group.
 * @param data The data structure containing information about the shell.
 * @return The process ID of the executed group, or -1 if an error occurs.
 */
pid_t	parse_manage_group(long type, t_list *grp, t_data *data)
{
	pid_t	pid;
	t_list	*extra;
	t_group	*cmds;

	pid = -1;
	extra = parse_extra(grp, data);
	if (extra != NULL)
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
