/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_manage_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/22 19:49:10 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*---PARSE RUN GROUP---*/

/*
Returns 0 if OK.
Returns 1 if can't create element in extra.
*/
static int	parse_sub_token(t_elem *e_elem, t_list *extra)
{
	if (is_extra(e_elem->key))
		return (!list_put(extra, e_elem->key, ft_strdup((char *)e_elem->val)));
	return (!list_put(extra, e_elem->key, e_elem->val));
}

static t_list	*parse_extra(t_list *grp, t_data *data)
{
	int		level;
	t_list	*extra;
	t_elem	*e_elem;

	level = 0;
	extra = list_new(cmp_int, NULL, free);
	e_elem = grp->head;
	while (extra != NULL && e_elem != NULL)
	{
		level += ((long)(e_elem->key) == L_PAR_L)
			+ ((long)(e_elem->key) == L_PAR_R) * (-1);
		if (level > 0 && parse_sub_token(e_elem, extra))
			return (list_free(extra), NULL);
		else if (level == 0 && parse_token(&e_elem, extra, data))
			return (list_free(extra), NULL);
		e_elem = e_elem->next;
	}
	return (extra);
}

static int	parse_grp_pipe(t_list *extra, t_list *cmds)
{
	t_elem	*e_elem;

	e_elem = extra->head;
	// printf("parse_grp_pipe - before WHILE\n");
	while (e_elem != NULL)
	{
		// printf("parse_grp_pipe - WHILE            \\\n");
		// printf("parse_grp_pipe - PARSE 1\n");


		if (parse_grp_cmd(e_elem, cmds) && e_elem == NULL)
		{
			// printf("parse_grp_pipe - parse_grp_cmd = fail\n");
			return (1);
		}



		// t_group *group = group_new(900);
		// group->cmds = cmds;
		// TEST_print_cmds(group);
		// printf("parse_grp_pipe - WHILE A           |\n");
		while (e_elem != NULL && (long)e_elem->key != L_PIPE)
			e_elem = e_elem->next;
		// printf("parse_grp_pipe - WHILE B           |\n");
		if (e_elem != NULL && e_elem->next == NULL)
			return (errors(1, NULL, "parse error near '|'", 258));
		// printf("parse_grp_pipe - WHILE C           |\n");
		if (e_elem != NULL)
			e_elem = e_elem->next;
		// printf("parse_grp_pipe - WHILE            /\n");
		// printf("parse_grp_pipe - PARSE 2\n");
	}
	// printf("parse_grp_pipe - DONE\n");
	return (0);
}

/*
Retrns 0 if OK.
*/
static int	parse_prepare_grp(t_list *extra, t_group *cmds)
{
	if (cmds->type & PARSER_PIPE)
	{
		// printf("parse_prepare_grp = parse_grp_pipe\n");
		// TEST_print_extra(extra->head);
		return (parse_grp_pipe(extra, cmds->cmds));
	}
	// printf("parse_prepare_grp = parse_grp_cmd\n");
	return (parse_grp_cmd(extra->head, cmds->cmds)); //no3
}

void	TEST_print_cmds(t_group	*cmds)
{
	t_elem	*head1;

	printf("\033[0;33mt_group CMDS\n");
	if (cmds == NULL)
	{
		printf("t_group	*cmds={NULL}\n");
		printf("\033[0m");
		return ;
	}
	printf("int type={%d}\n", cmds->type);
	if (cmds->cmds == NULL)
		printf("t_list *cmds={NULL}\n");
	else
	{
		head1 = cmds->cmds->head;
		int i = 0;
		while (head1 != NULL)
		{
			printf("cmd_info[%d]:\n", i);
			i++;
			printf("	level={%d}\n", ((t_cmd_info *)(head1->val))->level);
			printf("	flag ={%d}\n", ((t_cmd_info *)(head1->val))->flag);
			printf("	f_in ={%s}\n", ((t_cmd_info *)(head1->val))->f_in);
			printf("	f_out={%s}\n", ((t_cmd_info *)(head1->val))->f_out);
			printf("	sep  ={%s}\n", ((t_cmd_info *)(head1->val))->sep);
			head1 = head1->next;
		}
	}
	if (cmds->files == NULL)
		printf("t_list *files={NULL}\n");
	else
	{
		int i = 0;
		head1 = cmds->cmds->head;
		while (head1 != NULL)
		{
			printf("files[%d]: key={%ld} val={%ld}\n", i, (long)head1->key, (long)head1->val);
			i++;
			head1 = head1->next;
		}
	}
	printf("\033[0m");
}


void	TEST_print_extra(t_elem *curr)
{
	int i = 0;
	
	if (curr == NULL)
		return ;
	while (curr != NULL)
	{
		printf("\033[0;32mextra[%d] ", i);
		printf("key={%ld} ", (long)curr->key);
		printf("val={%s}\033[0m\n", (char *)curr->val);
		i++;
		curr = curr->next;
	}
}

/*
Returns pid value if OK.
Returns -1 if fail.
*/
pid_t	parse_manage_group(long type, t_list *grp, t_data *data)
{
	pid_t	pid;
	t_list	*extra;
	t_group	*cmds;

	// printf("parse_manage_group - type={%ld}\n", type);
	pid = -1;
	extra = parse_extra(grp, data);									// <<===== just work with the last one redir
	// printf("extra == NULL {%d}\n", extra == NULL);
	if (extra != NULL)
	{
		// TEST_print_extra(extra->head);
		cmds = group_new(type);
		if (!cmds)
			return (-1);
		//printf("parse_manage_group\n");
		//printf("Value of cmd->cmds->head->val: %ld\n", (long)cmds->cmds->head->key);
		if (parse_prepare_grp(extra, cmds)) //no4
			return (group_free(cmds), list_free(extra), -1);

			
		// TEST_print_cmds(cmds);

		// printf("list_size(cmds->cmds)={%d}\n", list_size(cmds->cmds));
		if (parse_manage_heredoc(cmds))
			return (group_free(cmds), list_free(extra), -1);
		// printf("list_size(cmds->cmds)={%d}\n", list_size(cmds->cmds));
		pid = executor(cmds, data);
		// printf("parse_manage_group		 g_signal={%d} pid={%d}\n", g_signal, pid);
		// printf("pid={%d}\n", pid);
		group_free(cmds);
		list_free(extra);
	}
	return (pid);
}
