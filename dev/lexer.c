/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:13:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/18 12:31:11 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static int	is_operator(const char c, const char c2)
{
	return (c == '(' || c == ')' || c == '|'
		|| (c == '&' && c2 == '&') || c == '<' || c == '>');
}

/*
Returns the position of the second quotes relative to the first quotes.
Returns 0 if didn't find second quotes.
*/
long	lexer_where_second_quotes(char c, const char *line)
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
int	lexer_get_quotes(t_list *toks, const char *line, long i, long *end)
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
int	lexer_get_operator(t_list *toks, const char *line, long i, long *end)
{
	long	t;

	t = get_operator_type(line, i);
	if (t == L_ANOTH)
		return (error_handler(1, "Error: get_operator_type", 0, 42));
	if (!list_put(toks, (int *)t, NULL))
		return (error_handler(1, "Erorr: lexer_get_operator", 1, 0));
	if (t == L_OR || t == L_AND || t == L_RE_DOC || t == L_RE_APP)
		*end = 1;
	else
		*end = 0;
	return (0);
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
			return (error_handler(1, "Erorr: lexer_get_quotes", 1, 0));
		if (end == 0)
			return (error_handler(1, "Error: unclosed quotes", 0, 0));
		*i = *i + end + 1;
	}
	else if (is_operator(line[*i], line[*i + 1]))
	{
		if (lexer_get_operator(toks, line, *i, &end))
			return (1);
		*i = *i + end + 1;
	}
	else if (line[*i])
	{
		if (lexer_get_word(toks, line, *i, &end))
			return (error_handler(1, "Erorr: lexer_get_word", 1, 0));
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
			return (error_handler(1, "Error: lexer", 1, 0));
		while (line[i] && is_space(line[i]))
			i++;
		if (lexer_get_token(toks, line, &i))
			return (1);
	}
	return (0);
}
