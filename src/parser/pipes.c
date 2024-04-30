/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:02 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/29 17:28:09 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_fd_in(t_cmd_info *cmd_info)
{
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
		return (errors(-1, "Error: fd_set_val: get_fd_in", 1, 0));
	fd->fds[1] = get_fd_out((t_cmd_info *)e_cmd->val);
	if (fd->fds[1] == -1)
		return (errors(-1, "Error: fd_set_val: get_fd_out", 1, 0));
	if (e_cmd != cmds->cmds->head && fd->fds[0] == STDIN_FILENO)
		fd->fds[0] = fd->pfd[0];
	return (0);
}

static void	fd_close(t_fd *fd, t_elem *e_cmd, int to_stop)
{
	if (to_stop != -1)
		close(to_stop);
	if (e_cmd->next)
		close(fd->pfd[1]);
	if (fd->fds[0] != STDIN_FILENO && fd->fds[0] != fd->pfd[0])
		close(fd->fds[0]);
	if (fd->fds[1] != STDOUT_FILENO && fd->fds[1] != fd->pfd[1])
		close(fd->fds[1]);
}

/*
Returns process pid.
Return -1 if error.
*/
int	pipes(t_group *cmds, t_data *data)
{
	int		pid;
	int		ret;
	int		to_stop;
	t_elem	*e_cmd;
	t_fd	fd;

	fd.pfd[0] = -1;
	e_cmd = cmds->cmds->head;
	while (e_cmd)
	{
		ret = fd_set_val(&fd, e_cmd, cmds);
		to_stop = fd.pfd[0];
		if (e_cmd->next && pipe(fd.pfd) == -1)
			return (errors(-1, "Error: pipes", 1, 0));
		if (e_cmd->next && fd.fds[1] == STDOUT_FILENO)
			fd.fds[1] = fd.pfd[1];
		if (((t_cmd_info *)e_cmd->val)->flag & CMD_SUB && ret == 0)
			pid = subshell_exe(e_cmd, data, &fd);
		else if (ret == 0)
			pid = common_exe(e_cmd, data, &fd, 1);
		fd_close(&fd, e_cmd, to_stop);
		e_cmd = e_cmd->next;
	}
	return (pid);
}