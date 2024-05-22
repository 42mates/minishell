/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:02 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/22 19:48:31 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_fd_in(t_cmd_info *cmd_info)
{
	// printf("fd={%s}\n", cmd_info->f_in);
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
	// printf("pipes 1\n");
	e_cmd = cmds->cmds->head;
	while (e_cmd->key == NULL)
		e_cmd = e_cmd->next;
	// printf("pipes 2\n");
	while (e_cmd)
	{
		// printf("pipes while 1 g_signal={%d} pid={%d}\n", g_signal, pid);
		g_signal = 0;
		// printf("pipes A\n");
		ret = fd_set_val(&fd, e_cmd, cmds);
		to_stop = fd.pfd[0];
		if (e_cmd->next && pipe(fd.pfd) == -1)
			return (errors(-1, "debug: pipes", "pipe failure", 1));
		if (e_cmd->next && fd.fds[1] == STDOUT_FILENO)
			fd.fds[1] = fd.pfd[1];
		if (((t_cmd_info *)e_cmd->val)->flag & CMD_SUB && ret == 0)
		{
			// printf("pipes subshell_exe\n");
			pid = subshell_exe(e_cmd, data, &fd);
			// printf("pipes subshell_exe 		g_signal={%d} pid={%d}\n", g_signal, pid);
		}
		else if (ret == 0)
		{
			// printf("pipes common_exe\n");
			pid = common_exe(e_cmd, data, &fd, 1);
			// printf("pipes common_exe		 g_signal={%d} pid={%d}\n", g_signal, pid);
			if (e_cmd->next != NULL && ((t_elem *)e_cmd->next)->key == NULL)
			{
				g_signal = 1;
			}
		}
		// printf("pipes while 2 		g_signal={%d} pid={%d}\n", g_signal, pid);
		fd_close(&fd, e_cmd, to_stop);
		e_cmd = e_cmd->next;
		// if (e_cmd->next && e_cmd->next)
		// 	g_signal = 1;
		while (e_cmd != NULL && e_cmd->key == NULL)
		{
			g_signal = 1;
			e_cmd = e_cmd->next;
		}
		// printf("pipes B\n");
	}
	return (pid);
}
