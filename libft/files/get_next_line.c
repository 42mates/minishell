/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:37:57 by mbecker           #+#    #+#             */
/*   Updated: 2024/03/29 17:26:42 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files.h"

//util function for gnl. Do not use outside.
static t_gnl_fd_data	*gnl_get_fd_data(int fd)
{
	static t_gnl_fd_data	fd_data[FD_MAX];
	int						i;

	i = 0;
	while (i < FD_MAX)
	{
		if (fd_data[i].fd == fd)
			return (&fd_data[i]);
		if (fd_data[i].fd == 0)
		{
			fd_data[i].fd = fd;
			return (&fd_data[i]);
		}
		i++;
	}
	return (NULL);
}

//util function for gnl. Do not use outside.
static char	*gnl_strjoin(char *oldtemp, char *stash)
{
	char	*newtemp;
	int		i;
	int		oldlen;

	if (oldtemp == NULL || stash == NULL)
		return (NULL);
	newtemp = (char *)malloc(ft_strlen(oldtemp) + ft_strlen(stash) + 1);
	if (!newtemp)
		return (NULL);
	i = 0;
	oldlen = ft_strlen(oldtemp);
	ft_strncpy(newtemp, oldtemp, oldlen);
	while (stash[i])
		newtemp[oldlen++] = stash[i++];
	newtemp[oldlen] = 0;
	free(oldtemp);
	return (newtemp);
}

//util function for gnl. Do not use outside.
static int	gnl_hasnewline(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

//util function for gnl. Do not use outside.
static char	*gnl_tempsplit(char *temp, char *stash)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (temp[i] != '\n' && temp[i] != 0)
		i++;
	if (temp[i] != 0)
		i++;
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	res = ft_strncpy(res, temp, i);
	while (temp[i])
		stash[j++] = temp[i++];
	free(temp);
	stash[j] = 0;
	return (res);
}

char	*get_next_line(int fd)
{
	t_gnl_fd_data	*fd_data;
	char			*temp;
	int				readval;

	fd_data = gnl_get_fd_data(fd);
	if (!fd_data)
		return (NULL);
	temp = ft_strdup(fd_data->stash);
	if (gnl_hasnewline(fd_data->stash))
		return (gnl_tempsplit(temp, fd_data->stash));
	readval = read(fd, fd_data->stash, BUFFER_SIZE);
	fd_data->stash[readval] = 0;
	if (readval <= 0 && temp[0] == 0)
	{
		free(temp);
		return (NULL);
	}
	temp = gnl_strjoin(temp, fd_data->stash);
	while (!gnl_hasnewline(temp) && readval > 0)
	{
		readval = read(fd, fd_data->stash, BUFFER_SIZE);
		fd_data->stash[readval] = 0;
		temp = gnl_strjoin(temp, fd_data->stash);
	}
	return (gnl_tempsplit(temp, fd_data->stash));
}
