/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/19 15:24:19 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int	is_or(long key)
{
	return (key == L_OR);
}

int	is_and(long key)
{
	return (key == L_AND);
}

int	is_or_and(long key)
{
	return (key == L_OR || key == L_AND);
}

/*---PARSE GROUPS---*/

/*
Returns 0 if OK.
*/
int	parse_fill_group(t_list *grp, t_elem **e_tok, long *type, long *level)
{
	long	key;

	key = (long)((*e_tok)->key);
	while (*e_tok != NULL && key == L_SPACE)
	{
		*e_tok = (*e_tok)->next;
		if (*e_tok != NULL)
			key = (long)((*e_tok)->key);
	}
	printf("===> parse_fill_group \\\n");
	while (*e_tok && (*level > 0 || (key != L_OR && key != L_AND)))
	{
		printf("===> parse_fill_group WHILE \\\n");
		*level = *level + (key == L_PAR_L);
		*level = *level - (key == L_PAR_R);
		*type = *type | ((*level > 0) << 5);
		*type = *type | (((key == L_PIPE) && *level == 0) << 6);
		if (!list_put(grp, (*e_tok)->key, (*e_tok)->val))
			return (errors(1, "Error: parse_fill_group", 1, 0));
		*e_tok = (*e_tok)->next;
		if (*e_tok != NULL)
			key = (long)((*e_tok)->key);
		printf("===> parse_fill_group WHILE /\n");
	}
	printf("===> parse_fill_group /\n");
	return (0);
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
	printf("\033[0;33m===> parse_groups \\\033[0m\n");
	while (e_tok)
	{
		printf("\033[0;32m===> parse_groups while \\\033[0m\n");
		grp = list_new(NULL, NULL, NULL);
		if (!grp)
			return (errors(1, "Error: parse_groups", 1, 0));
		level = 0;
		type = PARSER_BASE;
		if (parse_fill_group(grp, &e_tok, &type, &level))
			return (1);
		printf("===> parse_groups L=%ld\n", level);
		if (level)
		{
			list_free(grp);
			return (errors(1, "Error: parse error near '(' or ')'", 0, 42));
		}
		if (list_size(grp) && !list_put(grps, (void *)type, grp))
		{
			list_free(grp);
			return (errors(1, "Error: parse_groups", 1, 0));
		}
		if (list_size(grp) == 0)
			list_free(grp);
		if (e_tok && is_or_and((long)e_tok->key) && !list_put(grps, e_tok->key, NULL))
			return (errors(1, "Error: parse_groups", 1, 0));
		if (e_tok)
			e_tok = e_tok->next;
		printf("\033[0;32m===> parse_groups while /\033[0m\n");
	}
	printf("\033[0;33m===> parse_groups /\033[0m\n");
	return (0);
}

/*---PARSE CHECK OPERATORS---*/

/*
Returns 0 if OK.
*/
int	parse_is_or_and_valid(t_list *grps)
{
	int		need_grp;
	t_elem	*e_elem;
	t_elem	*e_prev;

	need_grp = 0;
	e_elem = grps->head;
	e_prev = NULL;
	printf("\033[0;33m===> parse_is_or_and_valid \\\033[0m\n");
	while (e_elem)
	{
	printf("\033[0;35m===> parse_is_or_and_valid key=%ld \\\033[0m\n", (long)e_elem->key);
		if (need_grp == 0 && is_or((long)e_elem->key))
			return (errors(1, "Error: parse error near '||'", 0, 42));
		else if (need_grp == 0 && is_and((long)e_elem->key))
			return (errors(1, "Error: parse error near '&&'", 0, 42));
		else
			need_grp = 1;
		if (need_grp == 1 && is_or_and((long)e_elem->key))
			need_grp = 0;
		e_prev = e_elem;
		e_elem = e_elem->next;
	}
	if (need_grp == 0 && is_or((long)e_prev->key))
		return (errors(1, "Error: parse error near '||'", 0, 42));
	if (need_grp == 0 && is_and((long)e_prev->key))
		return (errors(1, "Error: parse error near '&&'", 0, 42));
	printf("\033[0;33m===> parse_is_or_and_valid /\033[0m\n");
	return (0);
}

/*
Returns 0 if OK.
*/
int	parser(t_data *data, t_list *toks)
{
	t_list	*grps;

	grps = list_new(NULL, NULL, list_free);
	printf("===> parser 1 \\\n");
	if (!grps)
		return (1);
	printf("===> parser 1 /\n");
	printf("===> parser 2 \\\n");
	if (parse_groups(grps, toks))
		return (list_free(grps), 1);
	printf("===> parser 2 /\n");
	printf("===> parser 3 \\\n");
	if (!list_size(grps))
		return (list_free(grps), 0);
	printf("===> parser 3 /\n");
	printf("===> parser 4 \\\n");
	if (parse_is_or_and_valid(grps))
		return (list_free(grps), 1);
	printf("===> parser 4 /\n");
	printf("===> parser 5 \\\n");
	(void)data; //mockup
	// if (parse_run_groups(grps, data))
	// 	return (list_free(grps), 1);
	printf("===> parser 5 /\n");
	printf("===> parser 6 \\\n");
	list_free(grps);
	printf("===> parser 6 /\n");
	return (0);
}
