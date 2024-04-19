/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:13:18 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/19 12:53:20 by akurochk         ###   ########.fr       */
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

*/

int	str_contains(const char *s, const char c)
{
	if (s)
	{
		while (*s)
		{
			if (*s == c)
				return (1);
			s++;
		}
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/*
Returns 0 if OK.
Returns 1 if error.
*/
int	str_split(const char *s, const char *sep, char **dst1, char **dst2)
{
	int	i;
	int	j;

	if (!s || !sep)
		return (1);
	i = 0;
	while (s[i] && !str_contains(sep, s[i]))
		i++;
	j = i;
	*dst1 = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst1)
		return (1);
	while (j--)
		(*dst1)[j] = s[j];
	(*dst1)[i] = '\0';
	if (!s[i])
		*dst2 = NULL;
	else
		*dst2 = ft_strdup(s + i + 1);
	if (dst2)
		return (0);
	free(*dst1);
	return (1);
}

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
		if (str_split(env[i], "=", &key, &val))
			return (errors(1, "Error: env_parser", 1, 0));
		if (!list_put(env_lst, key, val))
			return (errors(1, "Error: env_parser", 1, 0));
	}
	return (0);
}

int	init_data(t_data *data, char **env)
{
	data->flag_exit = 0;
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
	return (0);
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
	// test_print_env(data.env_lst);					// TEST
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
				// printf("\n===> After Lexer\n\n");
				// test_print_tokens(toks);			// TEST
				printf("\n===> Before Parser\n\n");
				parser(&data, toks);
				printf("\n===> After Parser\n\n");
			}
			free(line);
		}
		list_free(toks);
	}
	free_data(&data);
	return (EXIT_SUCCESS); // return correct EXIT_CODE
}
