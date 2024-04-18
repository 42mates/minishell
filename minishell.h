/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:17:30 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/18 17:46:00 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
//# include "list/list.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <sys/ioctl.h>

typedef struct s_pipex
{
	int		nb_cmds;
	int		status;
	char	**envp;
	int		infile;
	int		outfile;
}			t_pipex;

int		execute(const char *cmd, char **envp);
char	*set_home_path(char *str, int free_str);
void	here_doc(const char *limiter);
int		pipex(char const **cmds, char **envp, int infile, int outfile);
//  in src directory

int		ft_echo(char **args);
int		ft_cd(char *path, t_list *list);
int		ft_pwd(void);

//  in builtins directory

#endif
