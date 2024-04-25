/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:13:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:39:14 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	is_operator(const char c, const char c2)
{
	return (c == '(' || c == ')' || c == '|'
		|| (c == '&' && c2 == '&') || c == '<' || c == '>');
}

/*
Returns token type.
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

/*
Returns 0 if OK.
*/
int	lexer_get_word(t_list *toks, const char *line, long i, long *end)
{
	char	*s_str;

	*end = 0;
	while (!is_space(line[i + *end])
		&& !is_operator(line[i + *end], line[i + *end + 1])
		&& line[i + *end] != '\'' && line[i + *end] != '\"' && line[i + *end])
		*end = *end + 1;
	s_str = ft_substr(line, i, *end);
	if (!s_str)
		return (1);
	if (!list_put(toks, (int *)L_WORD, s_str))
	{
		free (s_str);
		return (1);
	}
	return (0);
}
