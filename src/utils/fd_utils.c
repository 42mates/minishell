/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:02 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_fd_in(t_cmd_info *cmd_info)
{
	if (cmd_info == NULL)
		return (STDOUT_FILENO);
	if (!cmd_info->f_in)
		return (STDIN_FILENO);
	return (open(cmd_info->f_in, O_RDONLY, 0644));
}

int	get_fd_out(t_cmd_info *cmd_info)
{
	if (!cmd_info->f_out)
		return (STDOUT_FILENO);
	if (cmd_info->flag & CMD_APP)
		return (open(cmd_info->f_out, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (open(cmd_info->f_out, O_CREAT | O_WRONLY, 0644));
}

int	fd_set_val(t_fd *fd, t_elem *e_cmd, t_group *cmds)
{
	fd->fds[0] = get_fd_in((t_cmd_info *)e_cmd->val);
	if (fd->fds[0] == -1)
		return (errors(-1, (char *)e_cmd->val, strerror(errno), 1));
	fd->fds[1] = get_fd_out((t_cmd_info *)e_cmd->val);
	if (fd->fds[1] == -1)
		return (errors(-1, (char *)e_cmd->val, strerror(errno), 1));
	if (e_cmd != cmds->cmds->head && fd->fds[0] == STDIN_FILENO)
		fd->fds[0] = fd->pfd[0];
	return (0);
}
