/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:37:01 by akurochk          #+#    #+#             */
/*   Updated: 2024/04/24 16:14:57 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Cleans array.
Returns NULL.
*/
void	*free_str_array(char **array, int a)
{
	int		i;

	if (array == NULL)
		return (NULL);
	i = 0;
	if (a == -1)
	{
		while (array[i])
			free(array[i++]);
		return (free(array), NULL);
	}
	while (i < a)
		free (array[i++]);
	return (free(array), NULL);
}

/*
Returns allocated 2D array.
Or returns NULL.
*/
char	**init_str_array(int a, int b)
{
	int		i;
	char	**ret;

	if (a == 0 || b == 0)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * a);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < a)
	{
		ret[i] = (char *)malloc(sizeof(char *) * b);
		if (ret[i] == NULL)
			return (free_str_array(ret, i));
		i++;
	}
	return (ret);
}

void	parse_star_match(const char *pttrn, const char *str, char **buff)
{
	int	i;
	int	j;
	int	s_len;
	int	p_len;

	i = 1;
	s_len = ft_strlen(str);
	p_len = ft_strlen(pttrn);
	while (i < p_len + 1)
	{
		j = 1;
		while (j < s_len + 1)
		{
			if (pttrn[i - 1] == '*')
				buff[i][j] = (buff[i + 1][j] || buff[i][j + 1]);
			else if (str[j - 1] == pttrn[i - 1])
				buff[i][j] = buff[i - 1][j - 1];
			else
				buff[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	is_star_pattern(const char *str, const char *pttrn)
{
	int		i;
	int		s_len;
	int		p_len;
	char	**buff;

	s_len = ft_strlen(str);
	p_len = ft_strlen(pttrn);
	buff = init_str_array(p_len + 1, s_len + 1);
	if (buff == NULL)
		return (0);
	i = 1;
	buff[0][0] = 1;
	while (i < p_len + 1)
	{
		if (pttrn[i - 1] == '*')
			buff[i][0] = buff[i - 1][0];
		i++;
	}
	parse_star_match(pttrn, str, buff);
	i = buff[p_len][s_len];
	free_str_array(buff, p_len + 1);
	return (i);
}

int	have_star(struct dirent *s_dir, const char *word)
{
	return (((word[0] == '.' && s_dir->d_name[0] == '.')
			|| (word[0] != '.' && s_dir->d_name[0] != '.'))
		&& is_star_pattern(s_dir->d_name, word));
}

t_list	*parse_star_get(const char *word)
{
	t_list			*words;
	char			pwd[PATH_MAX];
	DIR				*dir;
	struct dirent	*s_dir;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (NULL);
	words = list_new(cmp_int, NULL, NULL);
	if (words == NULL)
		return (NULL);
	dir = opendir(pwd);
	if (dir == NULL)
		return (list_free(words), NULL);
	s_dir = readdir(dir);
	while (s_dir != NULL)
	{
		if (have_star(s_dir, word))
			list_put(words, (void *)L_WORD, ft_strdup(s_dir->d_name));
		s_dir = readdir(dir);
	}
	closedir(dir);
	if (list_size(words) == 0)
		return (list_free(words), NULL);
	return (words);
}

t_list	*parse_star(const char *word)
{
	if (!ft_strchr(word, '*'))
		return (NULL);
	if (ft_strchr(word, '/'))
		return (NULL);
	return (parse_star_get(word));
}