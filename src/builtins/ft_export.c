/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:39:16 by mbecker           #+#    #+#             */
/*   Updated: 2024/06/03 11:30:54 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_export(t_list *env)
{
	t_elem	*node;
	t_elem	*print;
	int		size;

	env = list_dup_str(env);
	size = list_size(env);
	while (size--)
	{
		node = env->head;
		print = env->head;
		while (node)
		{
			if (ft_strcmp(print->key, node->key) > 0)
				print = node;
			node = node->next;
		}
		if (!(!ft_strcmp(print->key, "_") && !ft_strcmp(print->val, "export")))
			print_var(print, "export ");
		list_del_one(env, print->key);
	}
	list_free(env);
}

static int	get_key_val(char *arg, char **key, char **val)
{
	char	*sep;
	char	*invalid;

	invalid = ft_strchrset(arg, INVALID_KEY);
	sep = ft_strchr(arg, '=');
	if (!*arg || *arg == '=' || ft_isdigit(*arg)
		|| (invalid && (!sep || invalid < sep)))
	{
		print_error("export", arg, "not a valid identifier");
		return (EXIT_FAILURE);
	}
	if (sep)
	{
		*key = ft_strndup(arg, sep - arg);
		*val = ft_strdup(sep + 1);
		return (EXIT_SUCCESS);
	}
	*key = ft_strdup(arg);
	*val = NULL;
	return (EXIT_SUCCESS);
}

/**
 * Updates the environment list with the provided arguments.
 * If no arguments are provided, it prints all environment variables.
 *
 * @param arg A parsed array of strings representing the arguments.
 * @param env A linked list representing the environment variables.
 * @return 0 on success.
 *
 * @note Export handles incorrect key names, but not `$`, `''` or `""`.
 * @note arg[0] must be "export" and arg[last] must be NULL.
 */
static int	builtin_export(char **arg, t_list *env)
{
	char	*key;
	char	*val;
	int		i;
	int		status;

	i = 0;
	status = EXIT_SUCCESS;
	if (!arg[1])
		print_export(env);
	while (arg[++i])
	{
		if (!get_key_val(arg[i], &key, &val))
		{
			list_replace(env, key, val);
			free(key);
		}
		else
			status = EXIT_FAILURE;
	}
	return (status);
}

int	ft_export(t_data *data, t_list *args)
{
	char	**argv;
	int		exit_status;

	(void)data;
	argv = list_to_argv(args);
	if (!argv)
		return (print_error("export", NULL, "malloc failed"), EXIT_FAILURE);
	exit_status = builtin_export(argv, data->env_lst);
	freetab(data->env, TRUE);
	data->env = list_to_env(data->env_lst);
	free(argv);
	g_signal = exit_status;
	return (exit_status);
}
