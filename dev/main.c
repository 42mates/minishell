/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:13:18 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/11 16:22:34 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1) // exit condition: signal or smth else ?
	{
		// prepare clear token var and read line
		line = readline("$ ");
		if (line && *line)
		{
			add_history(line);
			// analyse and get tokensfrom line
			// parse tokens
			printf("%s\n", line); // just for example
		}
		else if (line == NULL) // or if "exit\n"
			break ;
		// clear tokens sequence
	}
	// free all allocated memory
	return (EXIT_SUCCESS); // return correct EXIT_CODE
}
