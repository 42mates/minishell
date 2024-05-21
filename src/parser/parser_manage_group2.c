/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_manage_group2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/21 16:01:20 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Returns next token != L_SPACE.
Or returns NULL.
*/
static t_elem	*parse_get_next_nonspace_token(t_elem *e_elem)
{
	if (!e_elem)
		return (NULL);
	e_elem = e_elem->next;
	while (e_elem && (long)e_elem->key == L_SPACE)
		e_elem = e_elem->next;
	return (e_elem);
}

void	TEST_print_t_cmd_info(t_cmd_info *info)
{
	printf("cmd_info:\n");
	printf("	level={%d}\n", info->level);
	printf("	flag ={%d}\n", info->flag);
	printf("	f_in ={%s}\n", info->f_in);
	printf("	f_out={%s}\n", info->f_out);
	printf("	sep  ={%s}\n", info->sep);
}

/*
Returns 0 is OK.
*/
static int	parse_manage_token2(t_elem **e_elem, t_cmd_info *cmd_info)
{
	int fd;
	
	if ((long)(*e_elem)->key == L_RE_IN || (long)(*e_elem)->key == L_RE_DOC)
	{
		if ((long)(*e_elem)->key == L_RE_DOC)
			cmd_info->flag |= CMD_INS;
		else
			cmd_info->flag &= ~CMD_INS;
		*e_elem = parse_get_next_nonspace_token(*e_elem);
		if (*e_elem == NULL || (long)(*e_elem)->key != L_WORD)
			return (errors(1, NULL, "parse error near '<' or '<<'", 258));
		cmd_info->f_in = (*e_elem)->val;
		// TEST_print_t_cmd_info(cmd_info);									// TEST
		fd = open(cmd_info->f_in, O_RDONLY, 0644);
		if (fd == -1)
			return (errors(1, NULL, "No such file or directory", 1));
		close(fd);
		return (0);
	}
	if ((long)(*e_elem)->key == L_RE_OUT || (long)(*e_elem)->key == L_RE_APP)
	{
		if ((long)(*e_elem)->key == L_RE_APP)
			cmd_info->flag |= CMD_APP;
		else
			cmd_info->flag &= ~CMD_APP;
		*e_elem = parse_get_next_nonspace_token(*e_elem);
		if (*e_elem == NULL || (long)(*e_elem)->key != L_WORD)
			return (errors(1, NULL, "parse error near '<' or '<<'", 258));
		cmd_info->f_out = (*e_elem)->val;
		// TEST_print_t_cmd_info(cmd_info);									// TEST
		fd = open(cmd_info->f_out, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			return (errors(1, NULL, "Permission denied", 1));
		close(fd);
		return (0);
	}
	// printf("cmd_info:\n");
	return (0);
}

/*
Returns 0 is OK.
*/
static int	parse_manage_token(
				t_elem **e_elem, t_cmd_info *cmd_info, t_list *argv)
{
	if (*e_elem == NULL)
		return (errors(1, "debug: someting goes REALLY wrong", 0, 777));
	if ((long)(*e_elem)->key == L_PAR_L || (long)(*e_elem)->key == L_PAR_R)
	{
		cmd_info->level += ((long)(*e_elem)->key == L_PAR_L) + (-1)
			* ((long)(*e_elem)->key == L_PAR_R);
		cmd_info->flag |= CMD_SUB;
		if ((cmd_info->level == 1 && (long)(*e_elem)->key == L_PAR_L)
			|| (cmd_info->level == 0 && (long)(*e_elem)->key == L_PAR_R))
			return (0);
	}
	if ((long)(*e_elem)->key == L_SPACE && cmd_info->level == 0)
		return (0);
	if ((cmd_info->flag & CMD_SUB) && cmd_info->level == 0
		&& (long)(*e_elem)->key == L_WORD)
		return (errors(1, "debug: parse_manage_token", "extra token", 258));
	if (((long)(*e_elem)->key == L_WORD || cmd_info->level > 0)
		&& !list_put(argv, (*e_elem)->key, (*e_elem)->val))
		return (errors(1, "debug: parse_manage_token", "list_put", 0));
	// printf("argv added: key={%ld} val={%s}\n", (long)(*e_elem)->key, (char *)(*e_elem)->val);
	if (cmd_info->level > 0)
		return (0);
	return (parse_manage_token2(e_elem, cmd_info));
}

int	parse_grp_cmd(t_elem *e_elem, t_list *cmds)
{
	t_list		*argv;
	t_cmd_info	*cmd_info;

	cmd_info = cmd_info_init();
	if (cmd_info == NULL)
		return (errors(1, "debug: parse_grp_cmd", "cmd_info_init", 0));
	argv = list_new(NULL, NULL, NULL);
	if (argv == NULL)
		return (free(cmd_info), errors(1, "debug: parse_grp_cmd", "argv", 0));



	// Here code loses cmd_info
	while (e_elem != NULL && ((long)e_elem->key != L_PIPE || cmd_info->level))
	{
		if (parse_manage_token(&e_elem, cmd_info, argv))
			return (parse_grp_cmd_free(argv, cmd_info, 1));
		e_elem = e_elem->next;
		// 
	}
	if (!list_size(argv) && cmd_info->f_out == NULL && cmd_info->f_in == NULL)

		return (parse_grp_cmd_free(argv, cmd_info, 2)); //no2



	// Here code collects only the last one cmd_info
	if (e_elem == NULL || (long)e_elem->key == L_PIPE)
	{
		if (!list_put(cmds, argv, cmd_info))
			return (parse_grp_cmd_free(argv, cmd_info, 3));
		return (0);
	}
	return (parse_grp_cmd_free(argv, cmd_info, 1));
}
