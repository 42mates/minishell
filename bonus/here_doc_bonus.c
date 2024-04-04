/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:38:21 by mbecker           #+#    #+#             */
/*   Updated: 2024/03/20 14:50:53 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	redirect_input(const char *limiter, int fd)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strcmp(line, limiter) == '\n')
		{
			free(line);
			close(fd);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

void	here_doc(const char *limiter)
{
	pid_t	reader;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit_error("pipe");
	reader = fork();
	if (reader == 0)
	{
		close(pipe_fd[0]);
		redirect_input(limiter, pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		wait(NULL);
	}
}
