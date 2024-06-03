/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:22:05 by mbecker           #+#    #+#             */
/*   Updated: 2024/06/03 12:27:41 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_unset(t_data *data, t_list *args)
{
	t_elem	*tmp;
	t_elem	*env;

	tmp = args->head->next;
	while (tmp)
	{
		env = data->env_lst->head;
		while (env)
		{
			if (ft_strcmp(env->key, tmp->val) == 0)
			{
				list_del_one(data->env_lst, env->key);
				break ;
			}
			env = env->next;
		}
		tmp = tmp->next;
	}
	freetab(data->env, TRUE);
	data->env = list_to_env(data->env_lst);
	return (0);
}
