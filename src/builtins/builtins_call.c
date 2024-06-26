/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:05:29 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtins_exe(int i, t_elem *e_cmd, t_data *data, t_fd *fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		errors(-1, "debug: builtins_exe", "fork", 1);
	if (pid > 0)
		return (pid);
	if (redir_fd(fd->fds[0], fd->fds[1]))
		exit (1);
	if (fd->pfd[0] != -1)
		close(fd->pfd[0]);
	exit((*data->f_builtins[i])(data, e_cmd->key));
}

int	builtins_call(int i, t_elem *e_cmd, t_data *data, t_fd *fd)
{
	int	res;
	int	in_out[2];

	in_out[0] = dup(STDIN_FILENO);
	in_out[1] = dup(STDOUT_FILENO);
	if (redir_fd(fd->fds[0], fd->fds[1]))
	{
		close(in_out[0]);
		close(in_out[1]);
		return (errors(1, "debug: builtins_call", "redir_fd", 1));
	}
	res = (*data->f_builtins[i])(data, e_cmd->key);
	dup2(in_out[0], STDIN_FILENO);
	dup2(in_out[1], STDOUT_FILENO);
	close(in_out[0]);
	close(in_out[1]);
	return (res);
}
