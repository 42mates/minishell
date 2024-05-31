/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:25:30 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 16:50:43 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handler_signal(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 130;
	}
}

void	handler_heredoc(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	exit (130);
}

void	handler_executor(int signum)
{
	if (signum == SIGINT)
		write(2, "\n", 1);
	else if (signum == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
}
