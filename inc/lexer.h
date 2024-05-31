/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:59:44 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 16:35:43 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "structs.h"

int		lexer(const char *line, t_list *toks);
int		lexer_get_word(t_list *toks, const char *line, long i, long *end);
long	get_operator_type(const char *line, long i);
int		is_operator(const char c, const char c2);
int		is_space(const char c);

#endif