/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:20:40 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/10 15:15:09 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// util function for pipex. do not use elsewhere.
static void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
		
//void check_open_fds() {
//	int fd;
//	for (fd = 0; fd < sysconf(_SC_OPEN_MAX); fd++) {
//		if (fcntl(fd, F_GETFD) != -1) {
//			char fd_char = (char)(fd + 48);
//			write(2, &fd_char, 1);
//			write(2, " is open\n", 9);
//		}
//	}
//}

//// util function for pipex. do not use elsewhere.
//static void	handle_input(const char *cmd, t_pipex *data, char islast)
//{
//	close(data->pipefd[0]);
//	if (!islast)
//	{
//		dup2(data->pipefd[1], STDOUT_FILENO);
//		close(data->pipefd[1]);
//		execute(cmd, data->envp);
//		exit(1);
//	}
//	else
//	{
//		if (data->outfile != STDOUT_FILENO)
//		{
//			dup2(data->outfile, STDOUT_FILENO);
//			close(data->outfile);
//		}
//		execute(cmd, data->envp);
//		exit(127);
//	}
//}

//static void	handle_output(t_pipex *data, char islast)
//{
//	if (!islast)
//	{
//		close(data->pipefd[1]);
//		dup2(data->pipefd[0], STDIN_FILENO);
//		close(data->pipefd[0]);
//	}
//	else if (data->outfile != STDOUT_FILENO)
//		close(data->outfile);
//}

//// util function for pipex. do not use elsewhere.
//static void	child_process(const char *cmd, t_pipex *data, char islast)
//{
//	pid_t	pid;

//	if (!islast && pipe(data->pipefd) == -1)
//		exit_error("pipe");
//	pid = fork();
//	if (pid == -1)
//		exit_error("fork");
//	else if (pid == 0)
//		handle_input(cmd, data, islast);
//	else
//		handle_output(data, islast);
//}

static void	first_process(const char *cmd, t_pipex *data)
{
	pid_t	pid;

	if (pipe(data->pipefd) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (!pid)
	{
		close(data->pipefd[0]);
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[1]);
		execute(cmd, data->envp);
		exit(1);
	}
	//dup2(data->pipefd[0], STDIN_FILENO);
	//close(data->pipefd[0]);
	//close(data->pipefd[1]);
}

static void	middle_process(const char *cmd, t_pipex *data)
{
	pid_t	pid;

	if (pipe(data->pipefd) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (!pid)
	{
		dup2(data->pipefd[0], STDIN_FILENO);
		close(data->pipefd[0]);
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[1]);
		execute(cmd, data->envp);
		exit(1);
	}
	//else
	//{
	//	//dup2(data->pipefd[0], STDIN_FILENO);
	//	close(data->pipefd[0]);
	//	close(data->pipefd[1]);
	//}
}

static void	last_process(const char *cmd, t_pipex *data)
{
	pid_t	pid;

	close(data->pipefd[0]);
	close(data->pipefd[1]);
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (pid == 0)
	{
		close(data->pipefd[1]);
		dup2(data->pipefd[0], STDIN_FILENO);
		close(data->pipefd[0]);
		if (data->outfile != STDOUT_FILENO)
		{
			dup2(data->outfile, STDOUT_FILENO);
			close(data->outfile);
		}
		execute(cmd, data->envp);
		exit(127);
	}
	else
		close(data->outfile);
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
int pipex(char const **cmds, char **envp, int outfile)
{
	t_pipex data;
	int		i;
	int		nb_cmds;
	int		status;

	i = 0;
	nb_cmds = ft_tablen(cmds);
	status = 0;
	data.envp = envp;
	data.outfile = outfile;
	first_process(cmds[i++], &data);
	while (i < nb_cmds - 1)
		middle_process(cmds[i++], &data);
	last_process(cmds[i++], &data);
	while (wait(&status) > 0);
	return (status);
}
