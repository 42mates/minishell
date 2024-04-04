/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:40 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/02 19:45:53 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// util function for pipex. do not use elsewhere.
static void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

// util function for pipex. do not use elsewhere.
static void	handle_in_out(const char *cmd, t_pipex *data, char islast)
{
	if (!islast)
	{
		close(data->pipefd[0]);
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[1]);
		exec_cmd(cmd, data->envp);
		exit(1);
	}
	else
	{
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
		exec_cmd(cmd, data->envp);
		exit(127);
	}
}

// util function for pipex. do not use elsewhere.
static void	child_process(const char *cmd, t_pipex *data, char islast)
{
	pid_t	pid;

	if (!islast && pipe(data->pipefd) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (pid == 0)
		handle_in_out(cmd, data, islast);
	else
	{
		if (!islast)
		{
			close(data->pipefd[1]);
			dup2(data->pipefd[0], STDIN_FILENO);
			close(data->pipefd[0]);
		}
		else
			close(data->outfile);
	}
}

/**
 * Executes the pipe `|` command.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @param envp An array of strings containing the environment variables.
 * @return Returns 0 if the pipex command is executed successfully.
 * @note argv must follow this format: 
 * `{infile, cmd1, cmd2, ..., cmdn, outfile}`
 * @note use NULL in case of missing element: `{NULL, "ls -l", "wc", NULL}`
 */
int pipex(int argc, char const **argv, char **envp)
{
	t_pipex data;
	int		parsing_result;
	int		i;

	if (!parsing_result)
		return (1);
	data.envp = envp;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		here_doc(argv[2]);
	else
	{
		if (data.infile == -1)
			i++;
		if (dup2(data.infile, STDIN_FILENO) >= 0)
			close(data.infile);
	}
	while (i < argc - 1)
		child_process(argv[i++], &data, FALSE);
	child_process(argv[i], &data, TRUE);
	wait(NULL);
	if (parsing_result == -1)
		close(data.infile);
	return (0);
}
