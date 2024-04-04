/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:40 by mbecker           #+#    #+#             */
/*   Updated: 2024/03/20 14:50:56 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	report_and_clean(char *errorstr, char **tab1, char **tab2)
{
	cmd_error(errorstr);
	if (tab1)
		freetab(tab1, TRUE);
	if (tab2)
		freetab(tab2, TRUE);
	return (1);
}

char	**get_cmd_paths(char **envp, char *cmd)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
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

int	exec_cmd(const char *cmd, char **envp)
{
	char	**path;
	char	**args;
	int		i;

	if (!cmd || !*cmd || !envp)
		return (cmd_error(""), 1);
	args = ft_split_charset(cmd, SPACES);
	if (ft_strchr(cmd, '/'))
	{
		execve(args[0], args, envp);
		return (report_and_clean(args[0], args, NULL));
	}
	path = get_cmd_paths(envp, args[0]);
	if (!path)
	{
		write(2, PATH_ERR, 31);
		return (freetab(args, TRUE), 1);
	}
	i = 0;
	while (path[i])
		execve(path[i++], args, envp);
	return (report_and_clean(args[0], args, path));
}
