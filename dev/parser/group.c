/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:17:15 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 14:06:52 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_group	*group_new(int type)
{
	t_group	*grp;

	grp = (t_group *)malloc(sizeof(t_group));
	if (grp == NULL)
		return (NULL);
	grp->type = type;
	grp->cmds = list_new(NULL, list_free, free);
	if (grp->cmds == NULL)
	{
		free(grp);
		return (NULL);
	}
	grp->files = list_new(NULL, NULL, free);
	if (grp->files == NULL)
	{
		list_free(grp->cmds);
		free(grp);
		return (NULL);
	}
	return (grp);
}

void	group_free(void *grp)
{
	t_elem	*e_elem;

	e_elem = ((t_group *)grp)->files->head;
	while (e_elem)
	{
		unlink(e_elem->val);
		e_elem = e_elem->next;
	}
	list_free((void *)((t_group *)grp)->cmds);
	list_free((void *)((t_group *)grp)->files);
	free(grp);
}
