/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:13:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/23 12:56:05 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Returns the position of the second quotes relative to the first quotes.
Returns 0 if didn't find second quotes.
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

/*
Returns 0 if OK.
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
		{
			free (s_str);
			return (1);
		}
	}
	else
	{
		if (!list_put(toks, (int *)L_D_QUOT, s_str))
		{
			free (s_str);
			return (1);
		}
	}
	return (0);
}

/*
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

/*
Analyses token type in the line between whitespaces:
	- if ' or "
	- if | or > or < or & or ( or )
	- if word
Collects token in toks key=type. 
Returns 0 if OK.
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

/*
Collects tokens from the line to the toks collection.
Returns 0 if OK.
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
