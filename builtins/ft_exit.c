/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:35:28 by mbecker           #+#    #+#             */
/*   Updated: 2024/05/14 17:18:26 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_parsing(t_elem *head, long long *nb)
{
	t_elem	*tmp;

	tmp = head->next;
	if (!tmp)
		return (0);
	*nb = ft_atol(tmp->val);
	if (!ft_strisdigit(tmp->val) || (int)ft_strlen(tmp->val) != ft_numlen(*nb))
	{
		print_error("exit", tmp->val, "numeric argument required");
		return (2);
	}
	if (tmp->next)
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	return (0);
}

int	ft_exit(t_data *data, t_list *args)
{
	unsigned char	exit_status;
	long long		nb;

	write(STDOUT_FILENO, "exit\n", 5);
	nb = 0;
	exit_status = exit_parsing(args->head, &nb);
	if (exit_status == 1)
		return (exit_status);
	else if (!exit_status)
		exit_status = (unsigned char)nb;

	printf("\033[0;34mexiting program with code \033[1;34m%hhu\n\033[0m", exit_status);

	/*****  CASE 1 - use of exit()  *****/

	// freeing all variables. 
	//  Missing freeing of main's line string and toks list
	free_str_array(data->env, -1);
	list_free(data->env_lst);
	if (data->g_signal_str)
		free(data->g_signal_str);
	rl_clear_history();

	//exits directly the program
	exit(exit_status);

	/*****  CASE 2 - use of return  *****/
	//return (exit_status);
	// exit or return? see if parser needs freeing
}
//9223372036854775808 LONGMIN