/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:25:30 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/30 16:58:34 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handler_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
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
		write(2, "Exit: handler_executor\n", 5);
}
