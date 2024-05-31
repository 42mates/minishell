/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:22:52 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/31 16:36:37 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//cd
//cd notexisting
//cd xxx yyy

static int	cd_noargs(t_list *env)
{
	char	*home;
	char	*oldpwd;

	home = list_get(env, "HOME");
	if (!home)
		return (print_error("cd", NULL, "HOME not set"), EXIT_FAILURE);
	oldpwd = getcwd(NULL, 0);
	if (chdir(home))
	{
		print_error("cd", home, strerror(errno));
		return (EXIT_FAILURE);
	}
	list_replace(env, "OLDPWD", oldpwd);
	list_replace(env, "PWD", getcwd(NULL, 0));
	return (EXIT_SUCCESS);
}

/**
 * Changes the current working directory to the specified path.
 *
 * @param argv The path to the directory to change to.
 * @param env The environment variables list.
 * @return The exit status of the function.
 */
static int	builtin_cd(char **argv, t_list *env)
{
	char	*errorstr;
	int		exit_status;
	char	*oldpwd;

	if (!argv[1])
		return (cd_noargs(env));
	if (ft_tablen((const char **)argv) > 2)
		return (print_error("cd", NULL, "too many arguments"), EXIT_FAILURE);
	oldpwd = getcwd(NULL, 0);
	exit_status = chdir(argv[1]);
	if (*argv[1] && exit_status)
	{
		errorstr = strerror(errno);
		print_error("cd", argv[1], errorstr);
		free(oldpwd);
		return (-exit_status);
	}
	list_replace(env, "OLDPWD", oldpwd);
	list_replace(env, "PWD", getcwd(NULL, 0));
	return (EXIT_SUCCESS);
}

int	ft_cd(t_data *data, t_list *args)
{
	char	**argv;
	int		exit_status;

	argv = list_to_argv(args);
	if (!argv)
		return (print_error("cd", NULL, "malloc failed"), EXIT_FAILURE);
	exit_status = builtin_cd(argv, data->env_lst);
	free(argv);
	g_signal = exit_status;
	return (exit_status);
}
