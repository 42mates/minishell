/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:38:21 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/15 17:07:03 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Redirects input from the user until a specified delimiter is encountered.
 * The input is written to a file descriptor.
 *
 * @param limiter The delimiter to stop reading input.
 * @param fd The file descriptor to write the input to.
 */
static void	redirect_input(const char *limiter, int fd)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strcmp(line, limiter) == '\n')
		{
			free(line);
			close(fd);
			exit(EXIT_SUCCESS);
		}
		write(fd, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
}

/**
 * Implements the here document functionality by redirecting input from the user
 * until a specified delimiter is encountered.
 * The input is then passed to the parent process through a pipe.
 *
 * @param limiter The delimiter to stop reading input.
 */
void	here_doc(const char *limiter)
{
	pid_t	reader;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
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
