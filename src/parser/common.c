/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:53:13 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Executes a command based on the given mode.
 *
 * @param e_cmd The command element to be executed.
 * @param data The data structure.
 * @param fd The file descriptor structure.
 * @param mode For pipes (1). For the rest (0).
 * @return Returns 0 if the command execution is successful.
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

/**
 * Executes a command.
 *
 * This function is responsible for executing a command in the minishell.
 * It takes a group of commands and the data structure as input
 * and returns the process ID. The function sets up file descriptors for input
 * and output, and then calls the appropriate execution function based
 * on the command type.
 *
 * @param cmds The group of commands to execute.
 * @param data The data structure.
 * @return The process ID of the executed command.
 */
int	common(t_group *cmds, t_data *data)
{
	int		pid;
	t_fd	fd;
	t_elem	*cmd;

	cmd = cmds->cmds->head;
	fd.pfd[0] = -1;
	fd.fds[0] = get_fd_in(cmd->val);
	if (fd.fds[0] == -1)
		return (errors(-1, ((t_cmd_info *)cmd->val)->f_in, strerror(errno), 1));
	fd.fds[1] = get_fd_out(cmd->val);
	if (fd.fds[1] == -1)
		return (close(fd.fds[0]),
			errors(-1, ((t_cmd_info *)cmd->val)->f_out, strerror(errno), 1));
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
