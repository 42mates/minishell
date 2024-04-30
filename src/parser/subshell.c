/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:20:50 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/29 17:28:07 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	redir_fd(int in, int out)
{
	if (in != STDIN_FILENO)
	{
		if (dup2(in, STDIN_FILENO) == -1)
			errors(1, "Error: redir_fd: dup2 in", 1, 0);
		if (close(in) == -1)
			errors(1, "Error: redir_fd: close in", 1, 0);
	}
	if (out != STDOUT_FILENO)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			errors(1, "Error: redir_fd: dup2 out", 1, 0);
		if (close(out) == -1)
			errors(1, "Error: redir_fd: close out", 1, 0);
	}
	return (0);
}


int	subshell_exe(t_elem *e_cmd, t_data *data, t_fd *fd)
{
	int	pid;

	if (data->flag_env)
	{
		free_str_array(data->env, -1);
		data->env = env_make(data->env_lst);
		if (data->env == NULL)
			return (errors(-1, "Error: env_make", 1, 0));
		data->flag_env = 0;
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid > 0)
		return (pid);
	if (redir_fd(fd->fds[0], fd->fds[1]))
		return (-1);
	close(fd->pfd[0]);
	parser(data, (t_list *)e_cmd->key);
	exit (g_signal);
}

int	subshell(t_group *cmds, t_data *data)
{
	int		pid;
	t_fd	fd;

	fd.fds[0] = get_fd_in((t_cmd_info *)cmds->cmds->head->val);
	fd.pfd[0] = -1;
	if (fd.fds[0] == -1)
		return (errors(1, "Error: subshell: get_fd_in", 1, 0));
	fd.fds[1] = get_fd_out((t_cmd_info *)cmds->cmds->head->val);
	if (fd.fds[1] == -1)
	{
		close(fd.fds[0]);
		return (errors(1, "Error: subshell: get_fd_out", 1, 0));
	}
	pid = subshell_exe(cmds->cmds->head, data, &fd);
	if (fd.fds[0] != STDIN_FILENO)
		close (fd.fds[0]);
	if (fd.fds[1] != STDOUT_FILENO)
		close (fd.fds[1]);
	return (pid);
}