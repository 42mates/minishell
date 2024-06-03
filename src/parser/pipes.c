/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:02 by akurochk          #+#    #+#             */
/*   Updated: 2024/06/03 14:58:35 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Closes file descriptors based on the given conditions.
 *
 * @param fd The t_fd structure containing file descriptors.
 * @param e_cmd The t_elem structure representing the current command element.
 * @param to_stop The file descriptor to be closed.
 */
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

/**
 * To help with Norminette
 */
static t_elem	*pipes_pre(t_fd *fd, t_group *cmds, t_elem	**e_cmd)
{
	fd->pfd[0] = -1;
	*e_cmd = cmds->cmds->head;
	while (*e_cmd && (*e_cmd)->key == NULL)
		*e_cmd = (*e_cmd)->next;
	return (*e_cmd);
}

/**
 * To help with Norminette
 */
static int	pipes_util(t_fd *fd, t_elem *e_cmd, t_group *cmds, int *to_stop)
{
	g_signal = 0;
	*to_stop = fd->pfd[0];
	return (fd_set_val(fd, e_cmd, cmds));
}

/**
 * To help with Norminette
 */
static t_elem	*pipes_post(t_elem *e_cmd, t_fd *fd, int to_stop)
{
	fd_close(fd, e_cmd, to_stop);
	e_cmd = e_cmd->next;
	while (e_cmd != NULL && e_cmd->key == NULL)
	{
		g_signal = -1;
		e_cmd = e_cmd->next;
	}
	return (e_cmd);
}

/**
 * Executes a series of commands separated by pipes.
 *
 * @param cmds The group of commands to execute.
 * @param data The data structure containing.
 * @return The process ID of the last command executed.
 */
int	pipes(t_group *cmds, t_data *data)
{
	int		pid;
	int		ret;
	int		to_stop;
	t_elem	*e_cmd;
	t_fd	fd;

	e_cmd = pipes_pre(&fd, cmds, &e_cmd);
	while (e_cmd)
	{
		ret = pipes_util(&fd, e_cmd, cmds, &to_stop);
		if (e_cmd->next && pipe(fd.pfd) == -1)
			return (errors(-1, "debug: pipes", "pipe failure", 1));
		if (e_cmd->next && fd.fds[1] == STDOUT_FILENO)
			fd.fds[1] = fd.pfd[1];
		if (((t_cmd_info *)e_cmd->val)->flag & CMD_SUB && ret == 0)
			pid = subshell_exe(e_cmd, data, &fd);
		else if (ret == 0)
		{
			pid = common_exe(e_cmd, data, &fd, 1);
			if (e_cmd->next != NULL && ((t_elem *)e_cmd->next)->key == NULL)
				g_signal = -1;
		}
		e_cmd = pipes_post(e_cmd, &fd, to_stop);
	}
	return (pid);
}
