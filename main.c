/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:47:13 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/12 17:36:35 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, const char **av, char **env)
{
	if (ac < 3 || !env || !av)
		return (0);
	//int out = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//write(out, "", 1);

	int in = open(av[1], O_RDONLY | O_CREAT | O_APPEND, 0644);
	int out = 1;//open(av[4], O_RDONLY | O_CREAT | O_APPEND, 0644);

	pipex(av + 2, env, in, out);
	
	//pipex(av + 1, env, STDIN_FILENO, STDOUT_FILENO);

	return (0);
}