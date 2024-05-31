/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * To help with Norminette
 */
static void	parse_token_first(t_list **str, t_elem **e_elem)
{
	*str = list_new(cmp_int, NULL, NULL);
	list_put(*str, (*e_elem)->key, (*e_elem)->val);
	while ((*e_elem)->next && is_extra(((t_elem *)(*e_elem)->next)->key))
	{
		(*e_elem) = (*e_elem)->next;
		list_put(*str, (*e_elem)->key, (*e_elem)->val);
	}
}

/**
 * To help with Norminette
 */
static void	parse_token_second(t_list *extra, char *word, t_list *words)
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

/**
 * Parses a word (path, wildcards) and returns a list of possible words.
 *
 * This function takes a word and an environment list as input and parses
 * the word. If the word inside quotes, function returns NULL. Otherwise,
 * it sets the path of the word using the 'set_path' function and then calls
 * the 'parse_star' function to handle any wildcard characters in the word.
 *
 * @param word The word to be parsed.
 * @param env The environment list.
 * @param k The value of 'k' indicating the type of quoting.
 * @return A list of possible words, or NULL the word quoted or there are
 * no possible alternatives to represent the word.
 */
static t_list	*parse_word(char **word, long k)
{
	if (k == L_S_QUOT || k == L_D_QUOT)
		return (NULL);
	return (parse_star(*word));
}

/**
 * Parses a group element and adds it to the extra list. 
 * 
 * @param e_elem The current element in the group list.
 * @param extra The list where parsed tokens are stored.
 * @param data The data structure.
 * @param k The value to represent quoting symbols.
 * @return Returns 0 if the token was successfully recombined and solved,
 * 1 otherwise.
 */
int	parse_token(t_elem **e_elem, t_list *extra, t_data *data, long k)
{
	static t_elem_info	info;
	char				*word;
	t_list				*words;
	t_list				*str;

	if ((long)(*e_elem)->key == L_RE_APP)
		info.flag = 1;
	if (is_extra((*e_elem)->key))
	{
		parse_token_first(&str, e_elem);
		if (parse_token_field(str, data, &word, &info) == 1)
			return (list_free(str), 1);
		if (word == NULL)
			return (list_free(str), 0);
		words = parse_word(&word, k);
		if (words == NULL)
			list_put(extra, (void *)L_WORD, word);
		else
			parse_token_second(extra, word, words);
		list_free(str);
	}
	else
		list_put(extra, (*e_elem)->key, NULL);
	return (0);
}
