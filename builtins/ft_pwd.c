/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:36:35 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/02 17:34:05 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int builtin_pwd(void)
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

int	ft_pwd(t_data *data, t_list *args)
{
	(void)data;
	(void)args;
	return (builtin_pwd());
}