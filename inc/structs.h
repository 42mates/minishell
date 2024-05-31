/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:35:09 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/31 16:30:14 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_data	t_data;
typedef int				(*t_builtin)(t_data *, t_list *);

/*
builtins and f_builtins to connect commands with functions
and skip if-else constructions
*/
typedef struct s_data
{
	char		flag_exit;
	char		flag_env;
	char		**env;
	t_list		*env_lst;
	char		*builtins[7];
	t_builtin	f_builtins[7];
	char		*g_signal_str;
}	t_data;

typedef struct s_elem_info
{
	int	size;
	int	flag;
}	t_elem_info;

typedef struct s_chunk_info
{
	int	start;
	int	end;
}	t_chunk_info;

typedef struct s_cmd_info
{
	int		level;
	int		flag;
	char	*f_in;
	char	*f_out;
	char	*sep;
}	t_cmd_info;

typedef struct s_field_pack
{
	int				*i;
	int				*size;
	t_chunk_info	*c_info;
}	t_field_pack;

typedef struct s_group
{
	int			type;
	t_list		*cmds;
	t_list		*files;
}	t_group;

typedef struct s_fd
{
	int		fds[2];
	int		pfd[2];
}	t_fd;

#endif
