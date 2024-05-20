/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/20 12:52:01 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	parse_token_first_loop(t_list **str, t_elem **e_elem)
{
	*str = list_new(cmp_int, NULL, NULL);
	list_put(*str, (*e_elem)->key, (*e_elem)->val);
	while ((*e_elem)->next && is_extra(((t_elem *)(*e_elem)->next)->key))
	{
		(*e_elem) = (*e_elem)->next;
		list_put(*str, (*e_elem)->key, (*e_elem)->val);
	}
}

static void	parse_token_second_loop(t_list *extra, char *word, t_list *words)
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
