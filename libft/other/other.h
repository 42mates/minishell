/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:48:19 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/22 15:17:34 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHER_H
# define OTHER_H

# include "../libft.h"

void	freetab(char **tab, int heap);
//freetab.c

void	*ft_calloc(size_t nmemb, size_t size);
//ft_calloc.c

#endif
