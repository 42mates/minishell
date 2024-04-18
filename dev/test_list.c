/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:27:25 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/18 17:55:02 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// gcc test_list.c list.c -o test_list

int	main(void)
{
	printf("\n-INT-\n");

	t_list 	*ints = list_new(cmp_int, NULL, free);
	
	char	*s1 = malloc(sizeof(char) * 6);
	char	*s2 = malloc(sizeof(char) * 6);
	char	*s3 = malloc(sizeof(char) * 6);
	char	*s4 = malloc(sizeof(char) * 6);
	char	*s5 = malloc(sizeof(char) * 6);
	
	int		key1 = 0;
	int		key2 = 1;
	int		key3 = 5;
	int		key4 = 7;
	int		key5 = 3;

	strcpy(s1, "--1--");
	strcpy(s2, "--2--");
	strcpy(s3, "--3--");
	strcpy(s4, "--4--");
	strcpy(s5, "--5--");

	list_put(ints, &key1, s1);
	list_put(ints, &key2, s2);
	list_put(ints, &key3, s3);
	list_put(ints, &key4, s4);
	list_put(ints, &key5, s5);

// If key in list -> get val -> print val
	printf("\n==A==\n");
	if (list_contains_key(ints, &key1))
		printf("%s\n", (char *)list_get(ints, &key1));
	if (list_contains_key(ints, &key2))
		printf("%s\n", (char *)list_get(ints, &key2));
	if (list_contains_key(ints, &key3))
		printf("%s\n", (char *)list_get(ints, &key3));
	if (list_contains_key(ints, &key4))
		printf("%s\n", (char *)list_get(ints, &key4));
	if (list_contains_key(ints, &key5))
		printf("%s\n", (char *)list_get(ints, &key5));
	printf("size a: %d\n", list_size(ints));

// Delete by key -> if key in list -> get val -> print val
	printf("\n==B==\n");
	list_del_one(ints, &key2);
	list_del_one(ints, &key3);
	list_del_one(ints, &key4);
	if (list_contains_key(ints, &key1))
		printf("%s\n", (char *)list_get(ints, &key1));
	if (list_contains_key(ints, &key2))					// deleted
		printf("%s\n", (char *)list_get(ints, &key2));
	if (list_contains_key(ints, &key3))					// deleted
		printf("%s\n", (char *)list_get(ints, &key3));
	if (list_contains_key(ints, &key4))					// deleted
		printf("%s\n", (char *)list_get(ints, &key4));
	if (list_contains_key(ints, &key5))
		printf("%s\n", (char *)list_get(ints, &key5));
	printf("size b: %d\n", list_size(ints));

// Try to get nodes from list after del
	printf("\n==C==\n");
	t_elem *e_ptr = ints->head;
	printf("%s\n", (char *)(e_ptr->val));
	e_ptr = ints->head->next;
	printf("%s\n", (char *)(e_ptr->val));

// Try to get val after del nodes
	printf("\n==D==\n");
	printf("%s |\n", s1);
	printf("%s |\n", s2); // free = glitch
	printf("%s |\n", s3); // free = glitch
	printf("%s |\n", s4); // free = glitch
	printf("%s |\n", s5);

// Free all
	list_free(ints);




	printf("\n-STR-\n");
	t_list 	*strs = list_new(cmp_str, free, free);
	
	char	*st1 = malloc(sizeof(char) * 6);
	char	*st2 = malloc(sizeof(char) * 6);
	char	*st3 = malloc(sizeof(char) * 6);
	char	*st4 = malloc(sizeof(char) * 6);
	char	*st5 = malloc(sizeof(char) * 6);

	char	*skey1 = malloc(sizeof(char) * 6);
	char	*skey2 = malloc(sizeof(char) * 6);
	char	*skey3 = malloc(sizeof(char) * 6);
	char	*skey4 = malloc(sizeof(char) * 6);
	char	*skey5 = malloc(sizeof(char) * 6);

	strcpy(st1, "--a--");
	strcpy(st2, "--b--");
	strcpy(st3, "--c--");
	strcpy(st4, "--d--");
	strcpy(st5, "--e--");

	strcpy(skey1, "Key 1");
	strcpy(skey2, "Key 2");
	strcpy(skey3, "Key 3");
	strcpy(skey4, "Key 4");
	strcpy(skey5, "Key 5");

	list_put(strs, skey1, st1);
	list_put(strs, skey2, st2);
	list_put(strs, skey3, st3);
	list_put(strs, skey4, st4);
	list_put(strs, skey5, st5);

// If key in list -> get val -> print val
	printf("\n==A==\n");
	if (list_contains_key(strs, skey1))
		printf("%s\n", (char *)list_get(strs, skey1));
	if (list_contains_key(strs, skey2))
		printf("%s\n", (char *)list_get(strs, skey2));
	if (list_contains_key(strs, skey3))
		printf("%s\n", (char *)list_get(strs, skey3));
	if (list_contains_key(strs, skey4))
		printf("%s\n", (char *)list_get(strs, skey4));
	if (list_contains_key(strs, skey5))
		printf("%s\n", (char *)list_get(strs, skey5));
	printf("size a: %d\n", list_size(strs));

// Delete by key -> if key in list -> get val -> print val
	printf("\n==B==\n");
	list_del_one(strs, skey2);
	list_del_one(strs, skey3);
	list_del_one(strs, skey4);
	if (list_contains_key(strs, skey1))
		printf("%s\n", (char *)list_get(strs, skey1));
	if (list_contains_key(strs, skey2))					// deleted
		printf("%s\n", (char *)list_get(strs, skey2));
	if (list_contains_key(strs, skey3))					// deleted
		printf("%s\n", (char *)list_get(strs, skey3));
	if (list_contains_key(strs, skey4))					// deleted
		printf("%s\n", (char *)list_get(strs, skey4));
	if (list_contains_key(strs, skey5))
		printf("%s\n", (char *)list_get(strs, skey5));
	printf("size b: %d\n", list_size(strs));

// Try to get nodes from list after del
	printf("\n==C==\n");
	t_elem *e_str = strs->head;
	printf("%s\n", (char *)(e_str->val));
	e_str = strs->head->next;
	printf("%s\n", (char *)(e_str->val));

// Try to get val after del nodes
	printf("\n==D==\n");
	printf("|%s|\n", st1);
	printf("|%s|\n", st2);	// free = glitch
	printf("|%s|\n", st3);	// free = glitch
	printf("|%s|\n", st4);	// free = glitch
	printf("|%s|\n", st5);

// Free all
	list_free(strs);
}