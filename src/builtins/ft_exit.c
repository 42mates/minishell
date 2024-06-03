/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:35:28 by mbecker           #+#    #+#             */
/*   Updated: 2024/06/03 12:45:42 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	int		len;

	tmp = head->next;
	if (!tmp)
		return (0);
	*nb = ft_atol(tmp->val);
	len = (int)ft_strlen(tmp->val);
	if (*(char *)tmp->val == '+')
		len--;
	if (!ft_strisdigit(tmp->val) || len != ft_numlen(*nb))
	{
		print_error("exit", tmp->val, "numeric argument required");
		return (2);
	}
	if (tmp->next)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	return (0);
}

int	ft_exit(t_data *data, t_list *args)
{
	unsigned char	exit_status;
	int				should_exit;
	long long		nb;

	nb = 0;
	should_exit = 1;
	exit_status = exit_parsing(args->head, &nb);
	if (exit_status == 1)
		should_exit = 0;
	if (!exit_status)
		exit_status = (unsigned char)nb;
	if (should_exit == 1)
		data->flag_exit = 0;
	g_signal = exit_status;
	return (exit_status);
}
