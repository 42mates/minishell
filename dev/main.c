/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:13:18 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/15 17:09:16 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

MAIN loop:

start		-> READLINE	-> line
line		-> LEXER		-> tokens
tokens		-> PARSER		-> analaise tokens and get info about builtin(s)
builtin(s)	-> EXECUTE		-> result
result		-> POSTACTIONS	-> start/finish

BUILTINS

echo	- option -n
cd		- only a relative or absolute path
pwd		- no options
export	- no options
unset	- no options
env		- no options or arguments
exit	- no options

*/



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
			// analyse and get tokens from line
			// parse tokens
			// run builtins
			printf("%s\n", line); // instead of builtins 
		}
		else if (line == NULL) // or if "exit\n"
			break ;
		// clear tokens sequence
	}
	// free all allocated memory and any trash
	return (EXIT_SUCCESS); // return correct EXIT_CODE
}
