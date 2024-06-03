/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:44:00 by mbecker           #+#    #+#             */
/*   Updated: 2024/06/03 11:25:14 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/********** LEXER **********/

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

/********** ERRORS **********/

# define ERROR_PIPE				"syntax error near unexpected token `|'"
# define ERROR_AND				"syntax error near unexpected token `&&'"
# define ERROR_OR				"syntax error near unexpected token `||'"
# define ERROR_PARENTHESIS		"syntax error near unexpected token `(' or `)'"
# define ERROR_NEW_LINE			"syntax error near unexpected token `newline'"
# define CMD_NOT_FOUND "command not found"

/********** UTILS **********/

# define PROMPT "msh> "
# define H_PROMPT "> "
# define INVALID_KEY "!@#%^&*()-+={}[]|:;'\",<>./? \t\n\v\f\r"
# define STD_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

/********** PARSER **********/

# define PARSER_BASE	0b0010000
# define PARSER_PIPE	0b1000000
// >>
# define CMD_APP		0b001
// <<
# define CMD_INS		0b010
// subshell
# define CMD_SUB		0b100

#endif
