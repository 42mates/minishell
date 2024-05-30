/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:03:18 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/30 12:59:41 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Sets the current path by concatenating the current working directory
 * with a given string.
 *
 * @param str The string to concatenate with the current working directory.
 * @param env_lst The environment list.
 * @return char* The new string representing the updated path,
 * or NULL if an error occurs.
 */
char	*set_current_path(char *str)
{
	char	*cwd;
	char	*new_str;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errors(0, "getcwd: ", strerror(errno), 2), NULL);
	if (!ft_strcmp(cwd, "/") && str[1])
		*cwd = 0;
	new_str = ft_strjoin(cwd, str + 1, TRUE, FALSE);
	free(str);
	return (new_str);
}

/**
 * @brief Sets the parent path of a given string by removing the last directory
 * from the current working directory.
 *
 * @param str The string to set the parent path for.
 * @param env_lst The environment list.
 * @return char* The new string with the parent path set.
 */
char	*set_parent_path(char *str)
{
	char	*cwd;
	char	*new_str;
	int		parent;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errors(0, "getcwd: ", strerror(errno), 2), NULL);
	if (!str[2])
		str = ft_strjoin(str, "/", TRUE, FALSE);
	parent = ft_strrchr(cwd, '/') - cwd;
	cwd[parent] = 0;
	new_str = ft_strjoin(cwd, str + 2, TRUE, FALSE);
	free(str);
	return (new_str);
}

/**
 * Sets the home path for a given string.
 *
 * @param str The input string.
 * @param env_lst The environment list.
 * @return The modified string with the home path set.
 */
char	*set_home_path(char *str, t_list *env_lst)
{
	char	*home;
	char	*new_str;

	home = list_get(env_lst, "HOME");
	if (!home)
		return (errors(0, "error near `~'", "HOME not set", 2), NULL);
	if (!ft_strcmp(str, "~"))
		return (free(str), ft_strdup(home));
	new_str = ft_strjoin(home, str + 1, FALSE, FALSE);
	free(str);
	return (new_str);
}

/**
 * Checks if a string is a relative path or a wildcard and sets it accordingly.
 *
 * @param str The string to set the path for.
 * @param env_lst The environment list.
 * @return The modified string with the path set.
 */
char	*set_path(char *str, t_list *env_lst)
{
	if (!str || !*str)
		return (NULL);
	else if (!ft_strcmp(str, ".") || !ft_strncmp(str, "./", 2))
		str = set_current_path(str);
	else if (!ft_strcmp(str, "..") || !ft_strncmp(str, "../", 3))
		str = set_parent_path(str);
	else if (!ft_strcmp(str, "~") || !ft_strncmp(str, "~/", 2))
		str = set_home_path(str, env_lst);
	return (str);
}
