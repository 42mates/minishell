/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:47:13 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/24 15:06:17 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, const char **av, char **env)
{	
	if (!ac || !av || !env)
		return (write(2, "Check for protection condition in main\n", 39), 1);
	
	t_list *list = tab_to_list(env);
	//for (t_elem *node = list->head; node; node = node->next) print_var(node);

	ft_export((char **)av, list);
	
	//printf("\033[1;31mSTART\033[0;31m\n");
	char *x[] = {"export", NULL};
	ft_export(x, list);
	//printf("\033[1;31mEND\033[0m\n");

	list_free(list);

	return (0);
}
