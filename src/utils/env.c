/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:24:16 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/20 16:02:32 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**env_make(t_list *env)
{
	int		i;
	int		size;
	char	**res;
	t_elem	*e_env;

	size = list_size(env);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	e_env = env->head;
	res[size] = NULL;
	while (i < size)
	{
		res[i] = ft_str_concat((char *)e_env->key, '=', (char *)e_env->val, 1);
		if (res[i] == NULL)
			return (free_str_array(res, i));
		e_env = e_env->next;
		i++;
	}
	return (res);
}

int	env_rebuild(t_data *data)
{
	free_str_array(data->env, -1);
	data->env = env_make(data->env_lst);
	if (data->env == NULL)
		return (errors(-1, "debug: env_rebuild", "env_make", 1));
	data->flag_env = 0;
	return (0);
}
