/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:13:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Checks if a character is a whitespace character.
 *
 * @param c The character to check.
 * @return 1 if the character is a whitespace character, 0 otherwise.
 */
int	is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

/**
 * Checks if the given characters form an operator.
 *
 * @param c The first character to check.
 * @param c2 The second character to check, used to check "&&".
 * @return 1 if the characters form an operator, 0 otherwise.
 */
int	is_operator(const char c, const char c2)
{
	return (c == '(' || c == ')' || c == '|'
		|| (c == '&' && c2 == '&') || c == '<' || c == '>');
}

/**
 * Determines the type of operator at the given position in the input line.
 * 
 * @param line The input line.
 * @param i The position in the input line.
 * @return The type of operator at the given position.
 */
long	get_operator_type(const char *line, long i)
{
	if (line[i] == '(')
		return (L_PAR_L);
	if (line[i] == ')')
		return (L_PAR_R);
	if (line[i] == '|' && line[i + 1] == '|')
		return (L_OR);
	if (line[i] == '|')
		return (L_PIPE);
	if (line[i] == '&' && line[i + 1] == '&')
		return (L_AND);
	if (line[i] == '<' && line[i + 1] == '<')
		return (L_RE_DOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (L_RE_APP);
	if (line[i] == '<')
		return (L_RE_IN);
	if (line[i] == '>')
		return (L_RE_OUT);
	return (L_ANOTH);
}

/**
 * @brief Extracts a word from the given line and adds it to the token list.
 *
 * This function scans the line starting from the given index and extracts
 * a word until it encounters a space, an operator, a single quote, or
 * a double quote. The extracted word is then added to the token list.
 *
 * @param toks A pointer to the token list.
 * @param line The input line to scan.
 * @param i The starting index to begin scanning from.
 * @param end A pointer to a variable that will store the length of
 * the extracted word.
 * @return 0 if the word is successfully extracted and added to
 * the token list, 1 otherwise.
 */
int	lexer_get_word(t_list *toks, const char *line, long i, long *end)
{
	char	*s_str;

	*end = 0;
	while (line[i + *end] && !is_space(line[i + *end])
		&& !is_operator(line[i + *end], line[i + *end + 1])
		&& line[i + *end] != '\'' && line[i + *end] != '\"')
		*end += 1;
	s_str = ft_substr(line, i, *end);
	if (!s_str)
		return (1);
	if (!list_put(toks, (int *)L_WORD, s_str))
		return (free(s_str), 1);
	return (0);
}
