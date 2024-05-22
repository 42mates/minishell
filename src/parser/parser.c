/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/22 19:48:00 by akurochk         ###   ########.fr       */
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
			// printf("parse_wait_all	A1	 g_signal={%d} pid={%d}\n", g_signal, pid);
			if (g_signal != 1)
				g_signal = WEXITSTATUS(*status);

			// printf("parse_wait_all	A2	 g_signal={%d} pid={%d}\n", g_signal, pid);

			
			if (WIFSIGNALED(*status)) // 0 if was stopped by signal
			{
				// printf("parse_wait_all	B1	 g_signal={%d} pid={%d}\n", g_signal, pid);
				g_signal = WTERMSIG(*status);
				// printf("parse_wait_all	B2	 g_signal={%d} pid={%d}\n", g_signal, pid);
				
				if (g_signal != 131)
				{
					// printf("parse_wait_all	C1	 g_signal={%d} pid={%d}\n", g_signal, pid);
					g_signal += 128;
					// printf("parse_wait_all	C1	 g_signal={%d} pid={%d}\n", g_signal, pid);
				}
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
			// printf("parse_groups_exe		 g_signal={%d} pid={%d}\n", g_signal, pid);
			if (pid < 0)
			{
				// printf("parse_groups_exe (pid < 0)		 g_signal={%d} pid={%d}\n", g_signal, pid);
				return (1);
			}
			if (pid > 0)
			{
				// printf("parse_groups_exe (pid > 0)		 g_signal={%d} pid={%d}\n", g_signal, pid);
				parse_wait_all(pid, &status);
			}
			// printf("parse_groups_exe AFTER parse_wait_all		 g_signal={%d} pid={%d}\n", g_signal, pid);
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
