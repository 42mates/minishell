/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:17:30 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/15 13:17:31 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

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
// in execute/

void	here_doc(const char *limiter);
int		pipex(char const **cmds, char **envp, int infile, int outfile);

#endif
