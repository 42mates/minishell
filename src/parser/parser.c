/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Waits for all child processes to exit and updates the status.
 *
 * This function waits for all child processes to exit, updates the status
 * of the main process and g_signal. It takes the process ID of the main process 
 * and a pointer to the status variable as parameters.
 *
 * @param pid The process ID of the main process.
 * @param status A pointer to the status variable.
 */
static void	parse_wait_all(int pid, int *status)
{
	int	child;

	child = 1;
	while (child > 0)
	{
		child = waitpid(0, status, 0);
		if (pid == child)
		{
			if (g_signal != 1)
				g_signal = WEXITSTATUS(*status);
			if (WIFSIGNALED(*status))
			{
				g_signal = WTERMSIG(*status);
				if (g_signal != 131)
					g_signal += 128;
			}
		}
	}
}

/**
 * Checks if the given element of grps list connected with the previous one
 * by logical OR or AND operator.
 *
 * @param e_elem The grps element to check.
 * @param chain A pointer to the chain value.
 * @return 1 if the element is a logical operator, 0 otherwise.
 */
static int	parse_check_chain(t_elem *e_elem, int *chain)
{
	if ((g_signal == 0 && ((long)e_elem->key == L_OR))
		|| (g_signal != 0 && ((long)e_elem->key == L_AND)))
		return (1);
	*chain = 0;
	return (0);
}

/**
 * Runs child processes, handle and execute comands from groups inside grps list.
 * Waits for all child processes. Runs next group in chain of AND, OR operators.
 *
 * @param grps The list of groups to handle and execute.
 * @param data The data structure containing information about the minishell.
 * @return Returns 0 on success, 1 if an error occurred.
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

/**
 * Parses the tokens and constructs the command groups for execution.
 *
 * @param data The data structure.
 * @param toks The list of tokens to be parsed.
 * @return Returns 0 on success, 1 on failure.
 */
int	parser(t_data *data, t_list *toks)
{
	t_list	*grps;

	grps = list_new(NULL, NULL, list_free);
	if (grps == NULL)
		return (1);
	if (parse_groups(grps, toks->head, PARSER_BASE, 0))
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
