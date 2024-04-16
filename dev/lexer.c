/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:13:05 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/16 21:21:03 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static int	is_operator(char c)
{
	return (c == '(' || c == ')' || c == '|'
		|| c == '&' || c == '<' || c == '>');
}

/*
Analyses token type in the line between whitespaces:
	- if ' or "
	- if | or > or < or & or ( or )
	- if word
Collects token in toks key=type. 
Returns 0 if OK.
*/
static int	get_token(t_list *toks, char *line, long *i)
{
	long	type;

	if (line[*i] == '\'' || line[*i] == '\"')
	{
		// check type and are they closed
	}
	else if (is_operator(line[*i]))
	{
		// check type
	}
	else if (line[*i])
	{
		// check type, collect word as value
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
		if (get_token(toks, line, &i))
			return (1);
	}
	return (0);
}
