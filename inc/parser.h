/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:46 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/23 14:06:44 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PARSER_BASE	0b0010000
# define PARSER_PIPE	0b1000000

# define CMD_APP		0b001	// >>
# define CMD_INS		0b010	// <<
# define CMD_SUB		0b100	// subshell

#endif
