/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:50 by akurochk          #+#    #+#             */
/*   Updated: 2024/06/03 11:28:07 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	heredoc_file_swap(char *file, t_cmd_info *cmd_info, t_list *files)
{
	if (!list_put(files, 0, file))
		return (1);
	cmd_info->sep = cmd_info->f_in;
	cmd_info->f_in = file;
	if (cmd_info->f_in == NULL)
		return (1);
	return (0);
}

/**
 * Reads input from the user until a specific separator is encountered.
 * The input is written to a file descriptor.
 *
 * @param cmd_info The command information.
 * @param fd The file descriptor to write the input to.
 * @return Returns 0 on success, 1 on error.
 */
static int	heredoc_readline(t_cmd_info *cmd_info, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(H_PROMPT);
		if (line == NULL || !ft_strcmp(line, cmd_info->sep))
			break ;
		if (write(fd, line, ft_strlen(line)) == -1)
			return (1);
		if (write(fd, "\n", 1) == -1)
			return (1);
		free(line);
	}
	return (free(line), 0);
}

/**
 * Run the heredoc input management process.
 *
 * @param cmd_info The command information.
 * @param fd The file descriptor to write the input to.
 * @return Returns 0 in success.
 */
static int	heredoc_manage_input(t_cmd_info *cmd_info, int fd)
{
	int	sig;
	int	pid;

	sig = 0;
	pid = fork();
	if (pid == -1)
		return (errors(1, "debug: heredoc_manage_input", "fork", 1));
	if (pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &sig, 0);
	}
	if (pid == 0)
	{
		signal(SIGINT, handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
		if (heredoc_readline(cmd_info, fd))
			exit(errors(1, "debug: heredoc_manage_input", "heredoc_rdline", 1));
		exit(EXIT_SUCCESS);
	}
	return (WEXITSTATUS(sig) != 0);
}

/**
 * Creates a temporary file to store the heredoc input.
 * Manages the error handling.
 * Runs subproceses to read the input.
 */
static int	heredoc_init(t_cmd_info *cmd_info, t_list *files)
{
	int		fd;
	char	*file;
	char	*size;

	fd = -1;
	size = ft_uitoa(list_size(files));
	if (size == NULL)
		return (e_heredoc("Error: heredoc_init: size", NULL, size, fd));
	file = ft_str_concat("/var/tmp/minishell.tmp", 0, size, 0);
	if (file == NULL)
		return (e_heredoc("Error: heredoc_init: file", file, size, fd));
	if (access(file, F_OK) == 0 && unlink(file) == -1)
		return (e_heredoc("Error: heredoc_init: file exists", file, size, fd));
	fd = open(file, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (e_heredoc("Error: heredoc_init: file open", file, size, fd));
	if (heredoc_file_swap(file, cmd_info, files))
		return (e_heredoc("Error: heredoc_init: file swap", file, size, fd));
	if (heredoc_manage_input(cmd_info, fd))
		return (close(fd), free(size), 2);
	return (e_heredoc(NULL, file, size, fd));
}

/**
 * Parses and manages heredoc redirections for a group of commands.
 * 
 * @param cmds The group of commands to parse 
 * and manage heredoc redirections for.
 * @return Returns 0 if a heredoc redirection was encountered
 * and handled successfully, 1 otherwise.
 */
int	parse_manage_heredoc(t_group *cmds)
{
	int			res;
	t_elem		*e_cmd;
	t_cmd_info	*cmd_info;

	e_cmd = cmds->cmds->head;
	while (e_cmd != NULL)
	{
		if (e_cmd->key != NULL)
		{
			res = 0;
			cmd_info = (t_cmd_info *)e_cmd->val;
			if (cmd_info->flag & CMD_INS)
				res = heredoc_init(cmd_info, cmds->files);
			if (res == 2)
			{
				g_signal = 1;
				return (1);
			}
		}
		e_cmd = e_cmd->next;
	}
	return (0);
}
