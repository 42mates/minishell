/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:13:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/29 15:35:12 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Finds the index of the second occurrence 
 * of a specified character in a string.
 *
 * @param c The character to search for.
 * @param line The string in which to search for the character.
 * @return The index of the second occurrence of the character,
 * or 0 if not found.
 */
static long	lexer_where_second_quotes(char c, const char *line)
{
	long	i;

	i = 0;
	while (line[++i])
		if (line[i] == c)
			return (i);
	return (0);
}

/**
 * Extracts quotes from the given line and adds them to the token list.
 * This function searches for quotes in the line starting from the given
 * index 'i'. It determines the end index of the quotes and extracts
 * the substring between the quotes. The extracted substring is then added to
 * the token list along with the type of quotes.
 * 
 * @param toks The token list to add the extracted quotes.
 * @param line The input line to search for quotes.
 * @param i The starting index to search for quotes.
 * @param end A pointer to store the end index of the quotes.
 * @return Returns 0 if the quotes are successfully extracted and added
 * to the token list, 1 otherwise.
 */
static int	lexer_get_quotes(t_list *toks, const char *line, long i, long *end)
{
	char	*s_str;

	*end = lexer_where_second_quotes(line[i], line + i);
	if (*end == 0)
		return (0);
	s_str = ft_substr(line, i + 1, *end - 1);
	if (!s_str)
		return (1);
	if (line[i] == '\'')
	{
		if (!list_put(toks, (int *)L_S_QUOT, s_str))
			return (free(s_str), 1);
	}
	else
	{
		if (!list_put(toks, (int *)L_D_QUOT, s_str))
			return (free(s_str), 1);
	}
	return (0);
}

/**
Returns 0 if OK.
*/
static int	lexer_get_op(t_list *toks, const char *line, long i, long *end)
{
	long	t;

	t = get_operator_type(line, i);
	if (t == L_ANOTH)
		return (errors(1, "debug: lexer_get_op", "get_operator_type", 258));
	if (!list_put(toks, (int *)t, NULL))
		return (errors(1, "debug: lexer_get_op", "get_operator_type", 1));
	if (t == L_OR || t == L_AND || t == L_RE_DOC || t == L_RE_APP)
		*end = 1;
	else
		*end = 0;
	return (0);
}

/**
 * @brief Retrieves the next token from the input line and adds it
 * to the token list.
 *
 * This function analyzes the character at the current position in
 * the input line and determines the type of token it represents.
 * If the character is a single quote or double quote, it calls
 * the lexer_get_quotes() function to handle quotes.
 * If the character is an operator: "|", ">", "<", "&", "(" or ")" -
 * it calls the lexer_get_op() function to handle operators.
 * If the character is neither a quote nor an operator, it calls 
 * the lexer_get_word() function to handle words.
 *
 * @param toks A pointer to the token list.
 * @param line The input line.
 * @param i A pointer to the current position in the input line.
 * @return 0 if the token is successfully added to the token list,
 * 1 if there is an error.
 */
static int	lexer_get_token(t_list *toks, const char *line, long *i)
{
	long	end;

	if (line[*i] == '\'' || line[*i] == '\"')
	{
		if (lexer_get_quotes(toks, line, *i, &end))
			return (errors(1, "debug: lexer_get_token", "lexer_get_quotes", 1));
		if (end == 0)
			return (errors(1, (char *)line, "found unclosed quotes", 0));
		*i = *i + end + 1;
	}
	else if (line[*i] && is_operator(line[*i], line[*i + 1]))
	{
		if (lexer_get_op(toks, line, *i, &end))
			return (1);
		*i = *i + end + 1;
	}
	else if (line[*i])
	{
		if (lexer_get_word(toks, line, *i, &end))
			return (errors(1, "debug: lexer_get_token", "lexer_get_word", 1));
		*i = *i + end;
	}
	return (0);
}

/**
 * Collects tokens from the line to the toks collection.
 * Returns 0 if successful.
 *
 * @param line The input line to tokenize.
 * @param toks The collection to store the tokens.
 * @return 0 if successful, 1 otherwise.
 */
int	lexer(const char *line, t_list *toks)
{
	long	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] && is_space(line[i])
			&& !list_put(toks, (int *)L_SPACE, NULL))
			return (errors(1, "debug: lexer", "while loop", 1));
		while (line[i] && is_space(line[i]))
			i++;
		if (lexer_get_token(toks, line, &i))
			return (1);
	}
	return (0);
}
