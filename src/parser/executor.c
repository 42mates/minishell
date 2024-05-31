/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:29:51 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Executes the given group of commands by calling one of tree functions.
 * One function for working with pipes, second for subshells,
 * and last one for rest.
 *  
 * @param cmds The group of commands to execute.
 * @param data The data structure.
 * @return The process ID of the executed command.
 */
pid_t	executor(t_group *cmds, t_data *data)
{
	signal(SIGQUIT, handler_executor);
	signal(SIGINT, handler_executor);
	if (PARSER_PIPE & cmds->type)
		return (pipes(cmds, data));
	if (((t_cmd_info *)cmds->cmds->head->val)->flag & CMD_SUB)
		return (subshell(cmds, data));
	return (common(cmds, data));
}

/**
 * Returns the number corresponding to the built-in command.
 *
 * @param e_cmd The element containing the command.
 * @param data The data structure containing the list of built-in commands.
 * @return The number corresponding to the built-in command, or 7 if not found.
 */
int	get_builtins_num(t_elem *e_cmd, t_data *data)
{
	int		i;
	t_list	*elems;

	i = -1;
	elems = (t_list *)e_cmd->key;
	while (++i < 7)
		if (!ft_strcmp((char *)elems->head->val, (char *)data->builtins[i]))
			return (i);
	return (i);
}
