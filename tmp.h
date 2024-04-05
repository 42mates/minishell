#ifndef TMP_H
# define TMP_H

# include "libft/libft.h"

char	*set_home_path(char *str, int free_str);
// in set_home_path.c

int		execute(const char *cmd, char **envp);

#endif