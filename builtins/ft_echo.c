/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:41:45 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/20 12:44:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_option(char **args, int *i)
{
	int	j;

	while (args[++(*i)])
	{
		j = 1;
		if (!ft_strncmp(args[*i], "-n", 2))
		{
			while (args[*i][++j])
			{
				if (args[*i][j] != 'n')
					return (--(*i));
			}
		}
		else
			return (--(*i));
	}
	*i = 1;
	return (1);
}

/**
 * Reproduce the behavior of the echo command, with the `-n` option..
 *
 * @param args The NULL-terminated arguments to be written to the 
 * standard output.
 */
static int	builtin_echo(char **args)
{
	int		i;
	int		is_option;
	char	*str;

	if (!args[1])
		return (write(1, "\n", 1), 0);
	i = 0;
	is_option = check_option(args, &i);
	while (args[++i])
	{
		str = args[i];
		write(STDOUT_FILENO, str, ft_strlen(str));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!is_option)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

int	ft_echo(t_data *data, t_list *args)
{
	char	**argv;
	int		exit_status;

	(void)data;
	argv = list_to_argv(args);
	if (!argv)
		return (print_error("echo", NULL, "malloc failed"), EXIT_FAILURE);
	exit_status = builtin_echo(argv);
	free(argv);
	g_signal = exit_status;
	return (exit_status);
}
