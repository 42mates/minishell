/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:40 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/26 18:44:25 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_error(const char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found", 19);
	write(2, "\n", 1);
}

void	report_and_clean(char *errorstr, char **tab1, char **tab2)
{
	cmd_error(errorstr);
	if (tab1)
		freetab(tab1, TRUE);
	if (tab2)
		freetab(tab2, TRUE);
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

/**
 * Executes a command with the given arguments and environment variables.
 *
 * @param cmd The command to execute.
 * @param envp The array of environment variables.
 * @return execve exits the process if the command is found, otherwise 127.
 */
int	execute(const char *cmd, char **envp)
{
	char	**path;
	char	**args;
	int		i;

	if (!cmd || !*cmd || !envp)
		return (cmd_error(""), 127);
	args = ft_split_charset(cmd, SPACES);
	if (ft_strchr(cmd, '/'))
	{
		if (args[0][0] == '~')
			args[0] = set_home_path(args[0], TRUE);
		execve(args[0], args, envp);
		return (report_and_clean(args[0], args, NULL), 127);
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
	return (report_and_clean(args[0], args, path), 127);
}
