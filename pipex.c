/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:40 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/12 17:36:00 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// util function for pipex. do not use elsewhere.
static void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	first(const char *cmd, t_pipex *data, int pipefd[2], int prev[2])
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
		execute(cmd, data->envp);
		exit(1);
	}
	prev[0] = pipefd[0];
	prev[1] = pipefd[1];
}

static void last(const char *cmd, t_pipex *data, int prev[2])
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

		execute(cmd, data->envp);
		exit(127);
	}
	close(prev[0]);
	close(prev[1]);
}

/**
 * Executes the pipe `|` command.
 *
 * @param cmds A NULL-terminated array of strings containing the command line 
 * arguments.
 * @param envp An array of strings containing the environment variables.
 * @param outfile the final output fd.
 * @return Returns 0 if the pipex command is executed successfully.
 */
int pipex(char const **cmds, char **envp, int infile, int outfile)
{
	t_pipex data;
	int		i;
	int		pipefd[2];
	int		prev[2];

	i = 0;
	data.nb_cmds = 2; //DEBUG
	//data.nb_cmds = ft_tablen(cmds);
	//printf("nb_cmds: %d\n", data.nb_cmds);
	data.status = 0;
	data.envp = envp;
	data.infile = infile;
	data.outfile = outfile;
	printf("infile: %d\n", infile);
	printf("outfile: %d\n", outfile);

	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}

	first(cmds[i++], &data, pipefd, prev);

	while (i < data.nb_cmds - 1)
	{
		close(prev[1]);
		dup2(prev[0], STDIN_FILENO);
		close(prev[0]);
		first(cmds[i++], &data, pipefd, prev);
	}

	last(cmds[i++], &data, prev);

	while(wait(&(data.status)) > 0);
	if (outfile != STDOUT_FILENO)
		close(data.outfile);

	return (data.status);
}
