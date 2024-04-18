/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:13:18 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/18 17:54:23 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_aleks.h"

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
/* SIGINT = Ctrl + C */
void	main_begining(t_list **toks)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	errno = 0;
	*toks = list_new(cmp_int, NULL, free);
}

int	main(int ac, const char **av, char **env)
{
	char	*line;
	t_data	data;
	t_list	*toks;

	(void) ac;
	(void) av;
	// g_signal = 0;
	if (init_data(&data, env))
		return (EXIT_FAILURE);
	while (!data.flag_exit)
	{
		main_begining(&toks);
		line = ft_readline();
		if (line == NULL)
			data.flag_exit = 1;
		else if (line && *line)
		{
			if (lexer(line, toks) == 0)
			{
				printf("\n===> After Lexer\n\n");
				test_print_tokens(toks);
				// parser(&data, toks);
			}
			free(line);
		}
		list_free(toks);
	}
	free_data(&data);
	return (EXIT_SUCCESS); // return correct EXIT_CODE
}
