/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:17:30 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/23 17:27:05 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "inc/aleksei.h"
# include "inc/parser.h"
# include "inc/lexer.h"

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
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <fcntl.h>

// Prompt for minishell
// # define PROMPT "\033[0;34m( ͡° ͜ʖ ͡°)\033[0m> "
# define PROMPT "\033[0;34mmsh> \033[0m"
// Characters that cannot be part of a environment variable key/name 
# define INVALID_KEY "!@#%^&*()-+={}[]|:;'\",<>./? \t\n\v\f\r"

// Default $PATH
# define STD_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# define CMD_NOT_FOUND "command not found"

typedef struct s_pipex
{
	int		nb_cmds;
	int		status;
	char	**envp;
	int		infile;
	int		outfile;
}			t_pipex;

/**** SOURCE ****/

int		execute(char **args, char **envp);
void	here_doc(const char *limiter);
int		pipex(char ***cmds, char **envp, int infile, int outfile);

/**** BUILTINS ****/

int		ft_echo(t_data *data, t_list *args);
int		ft_cd(t_data *data, t_list *args);
int		ft_pwd(t_data *data, t_list *args);
int		ft_export(t_data *data, t_list *args);
int		ft_unset(t_data *data, t_list *args);
int		ft_env(t_data *data, t_list *args);
int		ft_exit(t_data *data, t_list *args);
void	print_var(t_elem *node, char *prefix);

/**** ERROR ****/

void	print_error(char *builtin, char *arg, char *msg);

/**** ENVIRONMENT ****/

void	env_set(char const **argv, t_list *env);
void	env_set__(char **args, t_list *env);
void	env_set_shlvl(t_list *env);
void	env_set_pwd(t_list *env);

#endif
