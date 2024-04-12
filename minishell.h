#ifndef TMP_H
# define TMP_H

# include "libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		nb_cmds;
	int		status;
	//int		pipefd[2];
	//int		prevfd[2];
	char	**envp;
}	t_pipex;

int		execute(const char *cmd, char **envp);
char	*set_home_path(char *str, int free_str);
// in execute/

void	here_doc(const char *limiter);
int		pipex(char const **cmds, char **envp, int infile, int outfile);

#endif