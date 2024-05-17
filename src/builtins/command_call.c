/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:34:14 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/17 16:15:11 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Checks possible paths.
Returns 0 if OK.
Returns 1 if error.
Returns 2 if permission denied.
*/
int	iter_access(char **f_ps, char **f_p, t_list *e_elem)
{
	int		i;
	char	*prev;
	char	*to_free;

	i = 0;
	prev = NULL;
	while (f_ps[i] != NULL)
	{
		to_free = f_ps[i];
		f_ps[i] = ft_str_concat(f_ps[i], '/', e_elem->head->val, 1);
		free(to_free);
		if (!f_ps[i])
			return (errors(1, "Error: ft_iterfps", 1, 0));
		if (access(f_ps[i], F_OK) == 0)
			prev = f_ps[i];
		if (access(f_ps[i], X_OK) == 0)
		{
			*f_p = ft_strdup(f_ps[i]);
			free_str_array(f_ps, -1);
			return (0);
		}
		i++;
	}
	return (1 + (prev != NULL));
}

/*
Tries to find simple comand.
Returns 0 if OK.
Returns 1 if error.
*/
int	command_acces(t_elem *e_cmd, char *path, char **f_path)
{
	int		res;
	char	**f_pathes;
	t_list	*e_elem;

	e_elem = e_cmd->key;
	if (ft_strchr(e_elem->head->val, '/') != NULL || path == NULL)
	{
		*f_path = ft_strdup(e_elem->head->val);
		if (access(*f_path, F_OK) == 0 && access(*f_path, X_OK) == -1)
			return (errors(1, "Error: permission denied", 0, 126));
		return (0);
	}
	f_pathes = ft_split(path, ':');
	if (f_pathes == NULL)
		errors(1, "Error: command_acces: ft_split", 1, 0);
	res = iter_access(f_pathes, f_path, e_elem);
	if (res == 0)
		return (0);
	free_str_array(f_pathes, -1);
	*f_path = NULL;
	if (res == 2)
		return (errors(1, "Error: permission denied", 0, 126));
	return (errors(1, "Error: command not found", 0, 127));
}

/*
Takes filepath, informstion about command and prepares argv for execve function.
Returns 0 if OK.
*/
int	prepare_argv(t_elem *e_cmd, char ***argv, char *filepath)
{
	int		i;
	t_elem	*e_curr;
	t_list	*elems;

	i = 0;
	elems = e_cmd->key;
	*argv = malloc(sizeof(char *) * (list_size(elems) + 1));
	if (!(*argv))
		errors(1, "Error: prepare_argv: malloc", 1, 0);
	e_curr = elems->head->next;
	(*argv)[i++] = ft_strdup(filepath);
	while (e_curr)
	{
		(*argv)[i] = ft_strdup((char *)e_curr->val);
		if ((*argv)[i] == NULL)
			if (free_str_array(*argv, i) == NULL)
				errors(1, "Error: prepare_argv: ft_strdup", 1, 0);
		e_curr = e_curr->next;
		i++;
	}
	(*argv)[i] = NULL;
	return (0);
}

/*
Calls the comand e_cmd by using execve
*/
int	command_call(t_elem *e_cmd, t_data *data, t_fd *fd)
{
	char	*path;
	char	*filepath;
	char	**argv;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		errors(-1, "Error: command_call: fork", 1, 0);
	if (pid > 0)
		return (pid);
	if (redir_fd(fd->fds[0], fd->fds[1]))
		exit(1);
	if (fd->pfd[0] != -1)
		close(fd->pfd[0]);
	path = list_get(data->env_lst, "PATH");
	if (command_acces(e_cmd, path, &filepath))
		exit(g_signal);
	if (prepare_argv(e_cmd, &argv, filepath))
		exit(g_signal);
	if (execve(filepath, argv, data->env) == -1)
		exit(errors(127, "Error: command_call: execve", 1, 0));
	return (1);
}
