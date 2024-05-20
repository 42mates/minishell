/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:14:49 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/20 12:43:11 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_set(char const **argv, t_list *env)
{
	char	*oldpwd;

	if (!list_get(env, "OLDPWD"))
	{
		oldpwd = ft_strdup("OLDPWD");
		list_replace(env, oldpwd, NULL);
	}
	env_set_pwd(env);
	env_set_shlvl(env);
	env_set__((char **)argv, env);
}

/**
 * Sets the value of the "_" environment variable to the last argument in the 
 * given array.
 * 
 * @note "_" is the last argument of the last command executed: 
 * @note  - Pipes are treated as one command -> `ls libft | cat | echo $_` will 
 * print the last argument before ls.
 * @note  - Redirections are not treated as arguments -> `ls >file && echo $_` 
 * will print `ls`.
 *
 * @param args The array of arguments.
 * @param env The list of environment variables.
 */
void	env_set__(char **args, t_list *env)
{
	list_replace(env, "_", ft_strdup(args[ft_tablen((const char **)args) - 1]));
}

/**
 * @brief Sets the value of the "SHLVL" environment variable.
 * 
 * This function checks if the "SHLVL" environment variable exists in the given
 * environment list. If it does not exist, it adds "SHLVL" with a value of "1".
 * If it exists, it increments the value by 1. If the value is less than 0, it
 * replaces the value with "0".
 * 
 * @param env The environment list.
 */
void	env_set_shlvl(t_list *env)
{
	char	*shlvl;
	int		shlvl_int;

	shlvl = list_get(env, "SHLVL");
	if (!shlvl)
		list_replace(env, "SHLVL", ft_strdup("1"));
	else
	{
		shlvl_int = ft_atoi(shlvl);
		if (shlvl_int < 0)
			list_replace(env, "SHLVL", ft_strdup("0"));
		else
		{
			shlvl_int++;
			list_replace(env, "SHLVL", ft_itoa(shlvl_int));
		}
	}
}

void	env_set_pwd(t_list *env)
{
	list_replace(env, "PWD", getcwd(NULL, 0));
}
