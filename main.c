/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:47:13 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/22 17:40:00 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	env_parser(t_list *env_lst, char **env)
{
	int		i;
	char	*key;
	char	*val;

	if (!env_lst)
		return (errors(1, "debug: env_parser", "env_lst - empty variable", 1));
	i = -1;
	while (env[++i])
	{
		if (ft_str_split(env[i], "=", &key, &val))
			return (errors(1, "debug: env_parser", "split", 1));
		if (!list_put(env_lst, key, val))
			return (errors(1, "debug: env_parser", "list_put", 1));
	}
	return (0);
}

int	init_data(t_data *data, char **env)
{
	data->flag_exit = 1;
	data->flag_env = 1;
	data->env = NULL;
	data->env_lst = list_new((t_cmp_key)ft_strcmp, free, free);
	if (!data->env_lst)
		return (errors(1, "debug: init_data", "env_lst == NULL", 1));
	data->g_signal_str = NULL;
	if (env_parser(data->env_lst, env))
		return (1);
	data->builtins[0] = "echo";
	data->builtins[1] = "cd";
	data->builtins[2] = "pwd";
	data->builtins[3] = "export";
	data->builtins[4] = "unset";
	data->builtins[5] = "env";
	data->builtins[6] = "exit";
	data->f_builtins[0] = &ft_echo;
	data->f_builtins[1] = &ft_cd;
	data->f_builtins[2] = &ft_pwd;
	data->f_builtins[3] = &ft_export;
	data->f_builtins[4] = &ft_unset;
	data->f_builtins[5] = &ft_env;
	data->f_builtins[6] = &ft_exit;
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
	*line = readline(PROMPT);
	if (*line && **line)
		add_history(*line);
}

int	main(int ac, const char **av, char **env)
{
	char	*line;
	t_data	data;
	t_list	*toks;

	if (!ac || !av || init_data(&data, env))
		return (EXIT_FAILURE);
	env_set(av, data.env_lst);
	while (data.flag_exit)
	{
		main_begining(&toks, &line);
		if (line == NULL)
			data.flag_exit = 0;
		else if (line != NULL && *line)
		{
			if (lexer(line, toks) == 0)
				parser(&data, toks);
			free(line);
		}
		list_free(toks);
		signal(SIGQUIT, SIG_IGN);
	}
	main_exit(&data);
	return (g_signal);
}
