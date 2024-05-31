/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_groups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:58:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Checks if the given key is a logical OR or logical AND operator.
 *
 * @param key The key to check.
 * @return 1 if the key is a logical OR or logical AND operator, 0 otherwise.
 */
static int	is_or_and(long key)
{
	return (key == L_OR || key == L_AND);
}

/**
 * Parses and fills a group with tokens.
 *
 * This function iterates through the token list and fills the given group
 * with tokens until it reaches the end of the list or encounters a logical
 * operator (OR, AND). The function keeps track of the nesting level of
 * parentheses and sets the type of the group.
 *
 * @param grp   The group to fill with tokens.
 * @param e_tok The current token in the list.
 * @param type  A pointer to the type of the group.
 * @param level A pointer to the level of parentheses.
 * @return      0 if successful, 1 if an error occurs.
 */
static int	parse_fill_group(
		t_list *grp, t_elem **e_tok, long *type, long *level)
{
	while (*e_tok != NULL && (long)((*e_tok)->key) == L_SPACE)
		*e_tok = (*e_tok)->next;
	while (*e_tok && (*level > 0 || !is_or_and((long)((*e_tok)->key))))
	{
		(*level) += ((long)((*e_tok)->key) == L_PAR_L);
		(*level) -= ((long)((*e_tok)->key) == L_PAR_R);
		(*type) |= ((*level > 0) << 5);
		(*type) |= ((((long)((*e_tok)->key) == L_PIPE) && *level == 0) << 6);
		if (!list_put(grp, (*e_tok)->key, (*e_tok)->val))
			return (errors(1, "Error: parse_fill_group", "list_put", 1));
		*e_tok = (*e_tok)->next;
	}
	return (0);
}

/**
 * Parses tokens into groups and adds them to a groups list.
 *
 * @param grps The list to add the parsed groups to.
 * @param e_tok The current token being parsed.
 * @param type The type of the current group.
 * @param level The level of the current group in case of parenthesis.
 * @return 0 if successful, 1 otherwise.
 */
int	parse_groups(t_list *grps, t_elem *e_tok, long type, long level)
{
	t_list	*grp;

	while (e_tok != NULL)
	{
		grp = list_new(NULL, NULL, NULL);
		if (grp == NULL)
			return (errors(1, "debug: parse_groups", "list_new", 1));
		level = 0;
		type = PARSER_BASE;
		if (parse_fill_group(grp, &e_tok, &type, &level))
			return (1);
		if (level != 0)
			return (list_free(grp), errors(1, NULL, ERROR_PARENTHESIS, 2));
		if (list_size(grp) && !list_put(grps, (void *)type, grp))
			return (list_free(grp), errors(1, "debug: parse_groups", "l64", 1));
		if (list_size(grp) == 0)
			list_free(grp);
		if (e_tok != NULL && is_or_and((long)(e_tok->key))
				&& !list_put(grps, e_tok->key, NULL))
			return (errors(1, "debug: parse_groups", "l68", 1));
		if (e_tok != NULL)
			e_tok = e_tok->next;
	}
	return (0);
}

/**
 * Checks if the groups in the given have errors near OR or AND operators.
 * 
 * @param grps The list of groups to check.
 * @return 0 if the groups are valid, otherwise an error code.
 */
int	parse_is_or_and_valid(t_list *grps)
{
	int		need_grp;
	t_elem	*e_elem;
	t_elem	*e_prev;

	need_grp = 0;
	e_elem = grps->head;
	e_prev = NULL;
	while (e_elem != NULL)
	{
		if (need_grp == 0 && ((long)e_elem->key) == L_OR)
			return (errors(1, NULL, ERROR_OR, 2));
		else if (need_grp == 0 && ((long)e_elem->key) == L_AND)
			return (errors(1, NULL, ERROR_AND, 2));
		else
			need_grp = 1;
		if (need_grp == 1 && is_or_and((long)(e_elem->key)))
			need_grp = 0;
		e_prev = e_elem;
		e_elem = e_elem->next;
	}
	if (need_grp == 0 && ((long)e_prev->key) == L_OR)
		return (errors(1, NULL, ERROR_OR, 2));
	if (need_grp == 0 && ((long)e_prev->key) == L_AND)
		return (errors(1, NULL, ERROR_AND, 2));
	return (0);
}
