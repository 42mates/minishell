/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/21 13:09:00 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	parse_wait_all(int pid, int *status)
{
	int	child;

	child = 1;
	while (child > 0)
	{
		child = waitpid(0, status, 0);
		if (pid == child)
		{
			g_signal = WEXITSTATUS(*status);
			if (WIFSIGNALED(*status)) // 0 if was stopped by signal
			{
				g_signal = WTERMSIG(*status);
				if (g_signal != 131)
					g_signal += 128;
			}
		}
	}
}

/*---PARSE RUN CHAIN---*/

static int	parse_check_chain(t_elem *e_elem, int *chain)
{
	if ((g_signal == 0 && ((long)e_elem->key == L_OR)) || (g_signal != 0
			&& ((long)e_elem->key == L_AND)))
		return (1);
	*chain = 0;
	return (0);
}

/*---PARSE GROUPS EXE---*/

/*
Returns 0 if OK.
*/
static int	parse_groups_exe(t_list *grps, t_data *data)
{
	int		chain;
	int		status;
	pid_t	pid;
	t_elem	*e_elem;

	chain = 0;
	e_elem = grps->head;
	while (e_elem != NULL)
	{
		if (chain == 0)
		{
			pid = parse_manage_group((long)e_elem->key, e_elem->val, data);
			if (pid < 0)
				return (1);
			if (pid > 0)
				parse_wait_all(pid, &status);
			chain = 1;
		}
		else if (parse_check_chain(e_elem, &chain))
			return (0);
		e_elem = e_elem->next;
	}
	return (0);
}

/*---PARSER---*/

/*
Returns 0 if OK.
*/
int	parser(t_data *data, t_list *toks)
{
	t_list	*grps;

	grps = list_new(NULL, NULL, list_free);
	if (grps == NULL)
		return (1);
	if (parse_groups(grps, toks))
		return (list_free(grps), 1);
	if (list_size(grps) == 0)
		return (list_free(grps), 0);
	if (parse_is_or_and_valid(grps))
		return (list_free(grps), 1);
	if (parse_groups_exe(grps, data))
		return (list_free(grps), 1);
	list_free(grps);
	return (0);
}
