/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:46:08 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/08 15:02:46 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "../libft.h"

typedef struct s_gnl_fd_data
{
	int				fd;
	char			stash[BUFFER_SIZE + 1];
}					t_gnl_fd_data;

char	*get_next_line(int fd);
//get_next_line.c

#endif