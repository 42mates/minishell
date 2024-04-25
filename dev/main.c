/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:13:18 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/25 15:29:45 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;
/*
BUILTINS:
echo	- option -n
cd		- only a relative or absolute path
pwd		- no options
export	- no options
unset	- no options
env		- no options or arguments
exit	- no options
*/

int	env_parser(t_list *env_lst, char **env)
{
	int		i;
	char	*key;
	char	*val;

	if (!env_lst || !env || !*env)
		return (errors(1, "Error: env_parser", 1, 0));
	i = -1;
	while (env[++i])
	{
		if (ft_str_split(env[i], "=", &key, &val))
			return (errors(1, "Error: env_parser", 1, 0));
		if (!list_put(env_lst, key, val))
			return (errors(1, "Error: env_parser", 1, 0));
	}
	return (0);
}

int	init_data(t_data *data, char **env)
{
	data->flag_exit = 1;
	data->flag_env = 1;
	data->env = NULL;
	data->env_lst = list_new(cmp_int, free, free);
	if (!data->env_lst)
		return (errors(1, "Error: init_data", 1, 0));
	if (env_parser(data->env_lst, env))
		return (1);
	data->builtins[0] = "echo";
	data->builtins[1] = "cd";
	data->builtins[2] = "pwd";
	data->builtins[3] = "export";
	data->builtins[4] = "unset";
	data->builtins[5] = "env";
	data->builtins[6] = "exit";
	data->f_builtins[0] = NULL; // &ft_echo;
	data->f_builtins[1] = NULL; // &ft_cd;
	data->f_builtins[2] = NULL; // &ft_pwd;
	data->f_builtins[3] = NULL; // &ft_export;
	data->f_builtins[4] = NULL; // &ft_unset;
	data->f_builtins[5] = NULL; // &ft_env;
	data->f_builtins[6] = NULL; // &ft_exit;
	return (0);
}

/*
Here code must free everything
*/
void	main_exit(t_data *data)
{
	write(STDOUT_FILENO, "exit\n", 5);
	free_str_array(data->env, -1);
	list_free(data->env_lst);
	free(data->g_signal_str);
	rl_clear_history();
}

/* new token list, read line, add history */
/* SIGINT = Ctrl + C */
void	main_begining(t_list **toks, char **line)
{
	signal(SIGINT, handler_signal);
	errno = 0;
	*toks = list_new(cmp_int, NULL, free);
	*line = readline(PROMT);
	if (*line && **line)
		add_history(*line);
}

void	main_postaction(t_list *toks)
{
	list_free(toks);
	signal(SIGQUIT, SIG_IGN);
}

//============TEST============
void	test_print_tokens(t_list *toks)
{
	if (!toks)
		printf("\n\033[0;31mtest_print_tokens FAIL\033[0m\n");
	printf("\n\033[0;34mtest_print_tokens \\\033[0m\n");
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
	printf("\033[0;34mtest_print_tokens /\033[0m\n\n");
}
//============TEST============

int	main(int ac, const char **av, char **env)
{
	char	*line;
	t_data	data;
	t_list	*toks;

	(void) ac;
	(void) av;
	if (init_data(&data, env))
		return (EXIT_FAILURE);
	while (data.flag_exit)
	{
		main_begining(&toks, &line);
		if (line == NULL)
			data.flag_exit = 0;
		else if (line != NULL && *line)
		{
			if (lexer(line, toks) == 0)
			{
				test_print_tokens(toks); //============TEST
				parser(&data, toks);
			}
			free(line);
		}
		main_postaction(toks);
	}
	main_exit(&data);
	return (g_signal);
}
