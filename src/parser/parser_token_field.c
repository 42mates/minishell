/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_field.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/16 16:29:27 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	parse_token_field_pre(t_list *str, t_data *data, t_list *chunks,
		t_elem_info *e_info)
{
	t_elem			*e_elem;
	t_chunk_info	*c_info;

	c_info = NULL;
	e_elem = str->head;
	while (e_elem)
	{
		if ((long)e_elem->key == L_S_QUOT || e_info->flag)
		{
			if (parse_alloc_c_info(&c_info, 0, ft_strlen((char *)e_elem->val)))
				return (1);
			e_info->size = e_info->size + c_info->end;
			if (!list_put(chunks, c_info, e_elem->val))
			{
				free(c_info);
				return (errors(1, "Error: parse_token_field_pre", 1, 0));
			}
		}
		else if (parse_collect_chunks((char *)e_elem->val, data, chunks,
				&(e_info->size)))
			return (1);
		e_elem = e_elem->next;
	}
	e_info->flag = 0;
	return (0);
}

static int	parse_token_field_cpy(t_list *chunks, char *word)
{
	int		i;
	int		j;
	t_elem	*e_elem;

	i = 0;
	e_elem = chunks->head;
	while (e_elem != NULL)
	{
		j = ((t_chunk_info *)e_elem->key)->start;
		while (j < ((t_chunk_info *)e_elem->key)->end)
			word[i++] = ((char *)e_elem->val)[j++];
		e_elem = e_elem->next;
	}
	return (0);
}

static void	parse_token_field_free_var(
	t_list *str, char **word, t_elem_info *info)
{
	t_elem	*e_elem;

	if (info->size != 0)
		return ;
	e_elem = str->head;
	while (e_elem)
	{
		if ((long)e_elem->key != L_WORD)
			return ;
		e_elem = e_elem->next;
	}
	free(*word);
	*word = NULL;
}

static void	parse_token_field_free(t_list *chunks, char **word)
{
	if (chunks)
		list_free(chunks);
	if (*word)
		free(*word);
}

int	parse_token_field(t_list *str, t_data *data, char **word, t_elem_info *info)
{
	t_list	*chunks;

	chunks = list_new(NULL, free, NULL);
	if (chunks == NULL)
		return (errors(1, "Error: parse_token_field", 1, 0));
	*word = NULL;
	info->size = 0;
	if (parse_token_field_pre(str, data, chunks, info))
		return (parse_token_field_free(chunks, word), 1);
	*word = (char *)malloc(sizeof(char) * (info->size + 1));
	if (*word == NULL)
		return (parse_token_field_free(chunks, word), 1);
	(*word)[info->size] = '\0';
	if (parse_token_field_cpy(chunks, *word))
		return (parse_token_field_free(chunks, word), 1);
	parse_token_field_free_var(str, word, info);
	list_free(chunks);
	return (0);
}
