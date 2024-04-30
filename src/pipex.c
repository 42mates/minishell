/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:40 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/29 13:01:46 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// util function for pipex. do not use elsewhere.
static void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

// util function for pipex. do not use elsewhere.
static void	first(char **cmd, t_pipex *data, int pipefd[2], int prev[2])
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(execute(cmd, data->envp));
	}
	prev[0] = pipefd[0];
	prev[1] = pipefd[1];
}

// util function for pipex. do not use elsewhere.
static void	middle(char **cmd, t_pipex *data, int pipefd[2], int prev[2])
{
	close(prev[1]);
	dup2(prev[0], STDIN_FILENO);
	close(prev[0]);
	first(cmd, data, pipefd, prev);
}

// util function for pipex. do not use elsewhere.
static void	last(char **cmd, t_pipex *data, int prev[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
	{
		close(prev[1]);
		dup2(prev[0], STDIN_FILENO);
		close(prev[0]);
		if (data->outfile != STDOUT_FILENO)
			dup2(data->outfile, STDOUT_FILENO);
		exit(execute(cmd, data->envp));
	}
	close(prev[0]);
	close(prev[1]);
}

/**
 * Executes the pipe `|` command.
 *
 * @param cmds A pointer to an array of strings containing the commands and 
 * their options: {{"ls", "-l"}, {"wc", "-c"}, NULL}.
 * @param envp An array of strings containing the environment variables.
 * @param infile the final input fd.
 * @param outfile the final output fd.
 * @return Returns the last command's exit status code.
 */
int	pipex(char ***cmds, char **envp, int infile, int outfile)
{
	t_pipex	data;
	int		i;
	int		pipefd[2];
	int		prev[2];

	i = 0;
	while (cmds && cmds[i++])
		;
	data = (t_pipex){--i, 0, envp, infile, outfile};
	i = 0;
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	first(cmds[i++], &data, pipefd, prev);
	while (i < data.nb_cmds - 1)
		middle(cmds[i++], &data, pipefd, prev);
	last(cmds[i++], &data, prev);
	while (wait(&(data.status)) > 0)
		;
	if (outfile != STDOUT_FILENO)
		close(data.outfile);
	return (data.status >> 8);
}
