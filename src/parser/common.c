/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:53:13 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/17 16:24:58 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/*
mode: 1 run builtins_exe for pipes function, 0 for builtins_call.
*/
int	common_exe(t_elem *e_cmd, t_data *data, t_fd *fd, int mode)
{
	int	i;

	if (list_size((t_list *)e_cmd->key) == 0)
		return (0);
	i = get_builtins_num(e_cmd, data);
	if (data->flag_env && env_rebuild(data) == -1)
		return (-1);
	if (i == 7)
		return (command_call(e_cmd, data, fd));
	if (mode)
		return (builtins_exe(i, e_cmd, data, fd));
	return (builtins_call(i, e_cmd, data, fd));
}


int	common(t_group *cmds, t_data *data)
{
	int		pid;
	t_fd	fd;
	t_elem	*cmd;

	cmd = cmds->cmds->head;
	fd.pfd[0] = -1; //debug
	fd.fds[0] = get_fd_in(cmd->val);
	if (fd.fds[0] == -1)
		return (errors(-1, "Error: common: fd_in", 1, 0));
	fd.fds[1] = get_fd_out(cmd->val);
	if (fd.fds[1] == -1)
		return (close(fd.fds[0]), errors(-1, "Error: common: fd_out", 1, 0));
	if (((t_cmd_info *)cmd->val)->flag & CMD_SUB)
		pid = subshell_exe(cmd, data, &fd);
	else
		pid = common_exe(cmd, data, &fd, 0);
	if (fd.fds[0] != STDIN_FILENO)
		close(fd.fds[0]);
	if (fd.fds[1] != STDOUT_FILENO)
		close(fd.fds[1]);
	return (pid);
}
