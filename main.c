/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:47:13 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/18 12:56:23 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, const char **av, char **env)
{
	int	res;
	char *grep[] = {"grep", "-e", "^\tif", "-e", "^\t\treturn", "main.c", NULL};
	
	if (!ac || !av || !env)
		return (execve("/bin/grep", grep, env));



	ft_pwd();

	//char buffer[1024];
	//int readval = read(0, buffer, 1024);
	//buffer[readval - 1] = 0;
	//ft_cd(buffer);

	ft_pwd();

	res = 0;
	return (res);
}
