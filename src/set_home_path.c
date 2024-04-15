/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_home_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:03:18 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/08 14:18:08 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * replaces ~ by the home path for a given string.
 * 
 * @param str The input string.
 * @param free_str Flag indicating whether to free the input string.
 * @return The modified string with the home path set, or the original string 
 * if the home path is not available (or unset).
 * @note The returned string must be freed.
 */
char	*set_home_path(char *str, int free_str)
{
	char	*home;
	char	*new_str;

	home = getenv("HOME");
	if (!home)
		return (str);
	new_str = ft_strjoin(home, str + 1, FALSE, FALSE);
	if (free_str)
		free(str);
	return (new_str);
}
