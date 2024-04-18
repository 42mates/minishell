/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:36:35 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/18 12:43:17 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (perror("pwd"), EXIT_FAILURE);
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		free(path);
	}
	return (EXIT_SUCCESS);
}
