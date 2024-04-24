/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:22:17 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/24 17:20:05 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define TRUE 1
# define FALSE 0

# define BUFFER_SIZE 4096
# define FD_MAX 512

# define SPACES " \t\n"
# define MALLOC_ERR "Error: malloc failed\n"
# define PATH_ERR "Error: invalid or missing path\n"

//# define PROMPT "\033[0;34m( ͡° ͜ʖ ͡°)\033[0m> "
# define PROMPT "\033[0;34m./test.export.sh: line X\033[0m> " //Remove for LENNT

#endif
