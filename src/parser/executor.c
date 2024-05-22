/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:29:51 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/22 19:07:02 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	executor(t_group *cmds, t_data *data)
{
	signal(SIGQUIT, handler_executor);
	signal(SIGINT, handler_executor);
	// printf("executor\n");
	if (PARSER_PIPE & cmds->type)
	{
		// printf("cmds->type={pipes}\n");
		return (pipes(cmds, data));
	}
	if (((t_cmd_info *)cmds->cmds->head->val)->flag & CMD_SUB)
	{
		// printf("((t_cmd_info *)cmds->cmds->head->val)->flag={subshell}\n");
		return (subshell(cmds, data));
	}
	// printf("cmds->type={common}\n");
	return (common(cmds, data));
}

/*
Returns num of builtin 0-6.
Returns 7 if it isn't builtin;
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
