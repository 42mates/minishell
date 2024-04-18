/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:55:29 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/18 17:54:23 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_aleks.h"

void	test_print_tokens(t_list *toks)
{
	if (!toks)
		printf("\ntest_print_tokens X\n");
	printf("\ntest_print_tokens A\n\n");
	t_elem *e_ptr = toks->head;
	long i = 0;
	while (e_ptr)
	{
		long  key = (long)(e_ptr->key);
		char *val = (char *)(e_ptr->val);
		printf("Token [%ld]	", i);
		printf("Key [%ld]		", key);
		printf("Val [%s]\n", val);
		e_ptr = e_ptr->next;
		i++;
	}
	printf("\ntest_print_tokens B\n\n");
}
