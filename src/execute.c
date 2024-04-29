/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:40 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/29 17:04:08 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_cmd_paths(char *cmd, char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		path = ft_split(envp[i] + 5, ':');
	else
		path = ft_split(STD_PATH, ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/", TRUE, FALSE);
		path[i] = ft_strjoin(path[i], cmd, TRUE, FALSE);
		if (!path[i])
			return (freetab(path, TRUE), NULL);
	}
	return (path);
}

/**
 * Executes a command with the given arguments and environment variables.
 *
 * @param args The command to execute and its arguments.
 * @param envp The array of environment variables.
 * @return execve exits the process if the command is found, otherwise 127.
 */
int	execute(char **args, char **envp)
{
	char	**path;
	int		i;

	if (!args || !*args)
		return (print_error(NULL, "", CMD_NOT_FOUND), 127);
	if (ft_strchr(args[0], '/'))
	{
		execve(args[0], args, envp);
		print_error(NULL, args[0], CMD_NOT_FOUND);
		freetab(args, TRUE);
		return (127);
	}
	path = get_cmd_paths(args[0], envp);
	i = 0;
	while (path[i])
		execve(path[i++], args, envp);
	print_error(NULL, args[0], CMD_NOT_FOUND);
	freetab(args, TRUE);
	freetab(path, TRUE);
	return (127);
}
