/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:05:29 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:06:46 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtins_exe(int i, t_elem *e_cmd, t_data *data, t_fd *fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		errors(-1, "Error: builtins_exe: fork", 1, 0);
	if (pid > 0)
		return (pid);
	if (redir_fd(fd->fds[0], fd->fds[1]))
		exit (1);
	close(fd->pfd[0]);
	// exit((*data->f_builtins[i])(e_cmd->key, data));	//<======== builtins
	(void)i;
	(void)e_cmd;
	(void)data;
	exit (-1); // error
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
		return (errors(1, "Error: builtins_call: redir_fd", 1, 0));
	}
	// res = (*data->f_builtins[i])(e_cmd->key, data);	//<======== builtins
	(void)i;
	(void)e_cmd;
	(void)data;
	res = -1; // error
	dup2(in_out[0], STDIN_FILENO);
	dup2(in_out[1], STDOUT_FILENO);
	close(in_out[0]);
	close(in_out[1]);
	return (res);
}

