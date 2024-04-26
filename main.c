/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:47:13 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/25 19:55:34 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, const char **av, char **env)
{	
	if (!ac || !av || !env)
		return (write(2, "Check for protection condition in main\n", 39), 1);

	t_list *env_list = tab_to_list(env);
	env_set(av, env_list);


	char *args[] = {"export", NULL};
	ft_export(args, env_list);

	return (0);
}
