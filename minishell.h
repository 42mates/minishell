/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:17:30 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/29 12:38:20 by mbecker          ###   ########.fr       */
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

// Prompt for minishell
# define PROMPT "\033[0;34m( ͡° ͜ʖ ͡°)\033[0m> "
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
char	*set_home_path(char *str, int free_str);
void	here_doc(const char *limiter);
int		pipex(char ***cmds, char **envp, int infile, int outfile);

/**** BUILTINS ****/

int		ft_echo(char **args);
int		ft_cd(char *path, t_list *list);
int		ft_pwd(void);
int		ft_export(char **arg, t_list *env);
void	print_var(t_elem *node, char *prefix);

/**** ERROR ****/

void	print_error(char *builtin, char *arg, char *msg);

/**** ENVIRONMENT ****/

void	env_set(char const **argv, t_list *env);
void	env_set__(char **args, t_list *env);
void	env_set_shlvl(t_list *env);
void	env_set_pwd(t_list *env);

#endif
