/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/16 16:32:48 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_alloc_c_info(t_chunk_info **c_info, int start, int end)
{
	*c_info = (t_chunk_info *)malloc(sizeof(t_chunk_info));
	if (*c_info == NULL)
		return (errors(1, "Error: parse_alloc_c_info", 1, 0));
	(*c_info)->start = start;
	(*c_info)->end = end;
	return (0);
}

void	parse_init_fpack(t_field_pack *f_pack, t_chunk_info *c_info, int *i,
		int *size)
{
	f_pack->i = i;
	f_pack->size = size;
	f_pack->c_info = c_info;
}

int	is_extra(void *key)
{
	return ((long)key == L_WORD || (long)key == L_S_QUOT
		|| (long)key == L_D_QUOT);
}

t_cmd_info	*cmd_info_init(void)
{
	t_cmd_info	*ret;

	ret = malloc(sizeof(t_cmd_info));
	if (ret == NULL)
		return (NULL);
	ret->level = 0;
	ret->flag = 0;
	ret->f_in = NULL;
	ret->f_out = NULL;
	ret->sep = NULL;
	return (ret);
}
