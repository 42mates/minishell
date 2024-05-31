/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:36:35 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/31 16:36:37 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_data *data, t_list *args)
{
	char	*path;

	(void)data;
	(void)args;
	path = getcwd(NULL, 0);
	if (!path)
	{
		print_error("pwd", "error retrieving current directory: getcwd",
			strerror(errno));
		return (EXIT_FAILURE);
	}
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		free(path);
	}
	g_signal = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
