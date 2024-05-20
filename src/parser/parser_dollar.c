/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:31 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/20 16:06:19 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	update_g_signal_str(t_data *data)
{
	if (data->g_signal_str != NULL)
		free(data->g_signal_str);
	data->g_signal_str = ft_itoa(g_signal);
	if (!data->g_signal_str)
		return (errors(1, "debug: update_g_signal_str", "!g_signal_str", 1));
	return (0);
}

static int	get_var_first(const char *s, t_data *data, char **ptr_env, int *pos)
{
	if (s[0] == '\0')
	{
		ptr_env = NULL;
		return (0);
	}
	if (s[0] == '?')
	{
		if (update_g_signal_str(data))
			return (1);
		*ptr_env = data->g_signal_str;
		*pos = *pos + 1;
		return (0);
	}
	return (2);
}

static int	get_var(const char *s, t_data *data, char **ptr_env, int *pos)
{
	int		i;
	int		ret;
	char	*var_name;

	i = 0;
	ret = get_var_first(s, data, ptr_env, pos);
	if (ret != 2)
		return (ret);
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (i == 0)
	{
		ptr_env = NULL;
		return (0);
	}
	var_name = ft_substr(s, 0, i);
	if (!var_name)
		return (errors(1, "Error: get_var", "var_name", 1));
	*ptr_env = (char *)list_get(data->env_lst, var_name);
	*pos = *pos + i;
	return (free(var_name), 0);
}

static int	parse_colect_from_env(char *s, t_data *data, t_list *chunks,
		t_field_pack *f_pack)
{
	char	*ptr_env;

	ptr_env = NULL;
	if (get_var(s + *(f_pack->i) + 1, data, &ptr_env, f_pack->i))
		return (1);
	if (!ptr_env && s[*(f_pack->i)] == '$')
		*(f_pack->size) += (++(f_pack->c_info->end) || 1);
	if (ptr_env != NULL)
	{
		if (parse_alloc_c_info(&(f_pack->c_info), 0, ft_strlen(ptr_env)))
			return (1);
		if (!list_put(chunks, f_pack->c_info, ptr_env))
		{
			free(f_pack->c_info);
			return (errors(1, "Error: parse_colect_from_env", "list_put", 1));
		}
		*(f_pack->size) += f_pack->c_info->end;
	}
	++(*(f_pack->i));
	return (0);
}

int	parse_collect_chunks(char *s, t_data *data, t_list *chunks, int *size)
{
	int				i;
	int				j;
	t_chunk_info	*c_info;
	t_field_pack	f_pack;

	i = 0;
	j = 0;
	c_info = NULL;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
		{
			(*size)++;
			i++;
		}
		if (parse_alloc_c_info(&c_info, j, i))
			return (1);
		if (!list_put(chunks, c_info, s))
			return (free(c_info), errors(1, "debug: parse_collect_c..", "", 1));
		parse_init_fpack(&f_pack, c_info, &i, size);
		if (s[i] == '$' && parse_colect_from_env(s, data, chunks, &f_pack))
			return (1);
		j = i;
	}
	return (0);
}
