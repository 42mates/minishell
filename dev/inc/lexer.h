/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:59:44 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:44:07 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*
Here we can set constants to represent lexical part of input.
*/

# define L_ANOTH	0	// if not 1-13 then another
# define L_SPACE	1	// all whitespaces
# define L_WORD		2	// any word or "comb of words"
# define L_PAR_L	3	// (
# define L_PAR_R	4	// )
# define L_PIPE		5	// |
# define L_OR		6	// ||
# define L_AND		7	// &&
# define L_RE_IN	8	// <
# define L_RE_OUT	9	// >
# define L_RE_DOC	10	// <<
# define L_RE_APP	11	// >>
# define L_S_QUOT	12	// '
# define L_D_QUOT	13	// "

int		lexer(const char *line, t_list *toks);
int		lexer_get_word(t_list *toks, const char *line, long i, long *end);
long	get_operator_type(const char *line, long i);
int		is_operator(const char c, const char c2);
int		is_space(const char c);

#endif