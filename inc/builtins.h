/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:39:52 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/31 16:40:15 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "structs.h"

/**** BUILTINS ****/

int		ft_echo(t_data *data, t_list *args);
int		ft_cd(t_data *data, t_list *args);
int		ft_pwd(t_data *data, t_list *args);
int		ft_export(t_data *data, t_list *args);
int		ft_unset(t_data *data, t_list *args);
int		ft_env(t_data *data, t_list *args);
int		ft_exit(t_data *data, t_list *args);

/**** UTILS ****/

void	print_var(t_elem *node, char *prefix);
int		builtins_exe(int i, t_elem *e_cmd, t_data *data, t_fd *fd);
int		builtins_call(int i, t_elem *e_cmd, t_data *data, t_fd *fd);

int		command_call(t_elem *e_cmd, t_data *data, t_fd *fd);

#endif
