/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:17:30 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/25 19:57:25 by mbecker          ###   ########.fr       */
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

/**** BUILTINS ****/

int		ft_echo(char **args);
int		ft_cd(char *path, t_list *list);
int		ft_pwd(void);
int		ft_export(char **arg, t_list *env);

void	builtin_error(char *builtin, char *arg, char *msg);
void	print_var(t_elem *node, char *prefix);
char	*get_last_arg(char **args);

/**** ENVIRONMENT ****/

void	env_set(char const **argv, t_list *env);
void	env_set__(char **args, t_list *env);
void	env_set_shlvl(t_list *env);
void	env_set_pwd(t_list *env);

#endif
