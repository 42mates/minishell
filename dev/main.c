/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:13:18 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/15 20:24:56 by akurochk         ###   ########.fr       */
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

BUILTINS:
echo	- option -n
cd		- only a relative or absolute path
pwd		- no options
export	- no options
unset	- no options
env		- no options or arguments
exit	- no options

We can use custom linked list with keys for nodes:
- ptr to head element:
	elem->key
	elem->content
	elem->next_elem
- set comporator for keys
- set destructor for keys and values

*/

int	init_data(t_data *data, char **env)
{
	(void) env; // mockup
	data->flag_exit = 0;
	//char		**env;
	//t_list		env_lts; // init new list (with malloc)
	// parce env to env_lst
	data->builtins[0] = "echo";
	data->builtins[1] = "cd";
	data->builtins[2] = "pwd";
	data->builtins[3] = "export";
	data->builtins[4] = "unset";
	data->builtins[5] = "env";
	data->builtins[6] = "exit";
	// set pointers to builtins functions
	/*
	data->f_builtins[0] = &ft_echo;
	data->f_builtins[1] = &ft_cd;
	data->f_builtins[2] = &ft_pwd;
	data->f_builtins[3] = &ft_export;
	data->f_builtins[4] = &ft_unset;
	data->f_builtins[5] = &ft_env;
	data->f_builtins[6] = &ft_exit;
	*/
	return (0); // set correct status
}

/*
Here code must free everything
*/
void	free_data(t_data *data)
{
	(void) data; // mockup
	return ;
}


char	*ft_readline(void)
{
	char	*line;

	line = readline(PROMT);
	if (line && *line)
		add_history(line);
	return (line);
}

/* new token list, read line, add history */
void	main_begining(t_list **tokens)
{
	errno = 0;
	tokens = NULL; // mockup // init new list (with malloc) 
}

/* clear tokens sequence */
void	main_ending(void *var)
{
	(void) var; // mockup
	return ;
}

int	main(int ac, const char **av, char **env)
{
	char	*line;
	t_data	data;
	t_list	*tokens;

	(void) ac;
	(void) av;
	init_data(&data, env);
	while (!data.flag_exit)
	{
		main_begining(&tokens);
		line = ft_readline();
		if (line == NULL)
			data.flag_exit = 1;
		else if (line && *line)
		{
			// analyse and get tokens from line
			// 		if OK parse tokens -> run builtins
			printf("%s\n", line); // mockup of builtins
			free (line);
		}
		main_ending(NULL);
	}
	free_data(&data);
	return (EXIT_SUCCESS); // return correct EXIT_CODE
}
