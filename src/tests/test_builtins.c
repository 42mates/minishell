/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:18:54 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/29 14:37:36 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	TEST_builtin(t_data *data, t_list *argv)
{
	t_elem	*arg;
	int		i;

	(void)data;
	arg = argv->head;
	i = 0;
	printf("\033[0;32m\nVals of l_list *argv \\\033[0m\n");
	while (arg != NULL)
	{
		printf("\033[0;32m   argv[%d]=[%s]\033[0m\n", i, (char *)arg->val);
		i++;
		arg = arg->next;
	}
	printf("\033[0;32mVals of l_list *argv / \n\n\033[0m");
	return (0);
}
