/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:22:52 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/22 16:28:22 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *path, t_list *list)
{
	char	*errorstr;
	int		exit_status;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	exit_status = chdir(path);
	if (path && *path && exit_status)
	{
		if (ft_strlen(path) < 256)
			errorstr = strerror(errno);
		else
			errorstr = "File name too long";
		builtin_error("cd", path, errorstr);
		return (-exit_status);
	}
	list_replace(list, "OLDPWD", oldpwd);
	list_replace(list, "PWD", getcwd(NULL, 0));
	return (EXIT_SUCCESS);
}

// PROTOTYPE FOR CD WORKING WITHOUT ARGUMENTS

// void	ft_cd(char *path)
//{
//	char *home;

//	home = getenv("HOME");
//	if (path && *path && chdir(path))
//		perror(path);
//	else if (chdir(home))
//		perror(home);
//}