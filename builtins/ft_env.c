/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:22:19 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/16 16:10:27 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data *data, t_list *args)
{
	t_elem	*env;

	env = data->env_lst->head;
	if (args->head->next)
		return (print_error("env", NULL, "too many arguments"), 1);
	while (env)
	{
		if (env->val)
			print_var(env, NULL);
		env = env->next;
	}
	g_signal = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
