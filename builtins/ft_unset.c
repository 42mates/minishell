/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:22:05 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/15 19:02:03 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *data, t_list *args) //arguments parsing yet to do
{
	t_elem	*tmp;
	t_elem	*env;

	tmp = args->head->next;
	while (tmp)
	{
		env = data->env_lst->head;
		while(env)
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
	return (0);
}