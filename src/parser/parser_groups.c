/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_groups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:58:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/21 12:48:29 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_or_and(long key)
{
	return (key == L_OR || key == L_AND);
}

/*
Returns 0 if OK.
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

void	TEST_print_t_list_GRPS(t_list *grps)
{
	t_elem	*curr = grps->head;
	t_elem	*g_cu;

	printf("\033[0;35mTEST_print_t_list_GRPS\n");
	while (curr != NULL)
	{
		if (curr->val != NULL)
		{
			g_cu = (t_elem *)(((t_list *)(curr->val)))->head;
			printf("grps key_g={%ld}\n", (long)(curr->key));
			while (g_cu != NULL)
			{
				printf("grps val_g={key={%ld} ", (long)(g_cu->key));
				printf("val={%s}}\n", (char *)(g_cu->val));
				g_cu = g_cu->next;
			}
		}
		else
		{
			printf("grps key={%ld}\n", (long)(curr->key));
			printf("grps val={NULL}\n");
		}
		curr = curr->next;
	}
	printf("\033[0m");
}

/*
Returns 0 if OK.
*/
int	parse_groups(t_list *grps, t_list *toks)
{
	t_list	*grp;
	t_elem	*e_tok;
	long	type;
	long	level;

	e_tok = toks->head;
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
			return (list_free(grp), errors(1, NULL, "parse error near '(' or ')'", 258));
		if (list_size(grp) && !list_put(grps, (void *)type, grp))
			return (list_free(grp), errors(1, "debug: parse_groups", "l64", 1));
		if (list_size(grp) == 0)
			list_free(grp);
		if (e_tok != NULL && is_or_and((long)(e_tok->key)) && !list_put(grps, e_tok->key, NULL))
			return (errors(1, "debug: parse_groups", "l68", 1));
		if (e_tok != NULL)
			e_tok = e_tok->next;
	}
	return (0);
}

/*
Checks errorsnear || and &&.
Returns 0 if OK.
Returns 1 if error.
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
			return (errors(1, NULL, "parse error near '||'", 258));
		else if (need_grp == 0 && ((long)e_elem->key) == L_AND)
			return (errors(1, NULL, "parse error near '&&'", 258));
		else
			need_grp = 1;
		if (need_grp == 1 && is_or_and((long)(e_elem->key)))
			need_grp = 0;
		e_prev = e_elem;
		e_elem = e_elem->next;
	}
	if (need_grp == 0 && ((long)e_prev->key) == L_OR)
		return (errors(1, NULL, "parse error near '||'", 258));
	if (need_grp == 0 && ((long)e_prev->key) == L_AND)
		return (errors(1, NULL, "parse error near '&&'", 258));
	return (0);
}
