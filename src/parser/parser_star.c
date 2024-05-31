/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:37:01 by akurochk          #+#    #+#             */
/*   Updated: 2024/05/31 15:43:18 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Frees the memory allocated for a string array.
 *
 * @param array The string array to be freed.
 * @param a The index until which the array elements should be freed.
 * If a is -1, all elements in the array will be freed.
 * @return NULL.
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

/**
 * @brief Compares pattern and string in current position.
 * 
 * @param w The wildcard pattern.
 * @param p The array containing the pointers.
 * @return Returns 0 if there is a match, 1 otherwise.
 */
static int	handle_star(const char *w, const char **p)
{
	if (*p[0] == '*' && (p[0] == w || *(p[0] - 1) != '\\'))
	{
		p[2] = p[0]++;
		p[3] = p[1];
	}
	else if (p[2])
	{
		p[0] = p[2] + 1;
		p[1] = ++(p[3]);
	}
	else
		return (1);
	return (0);
}

/**
 * @brief Checks if there is a match between string and wildcard patern.
 * 
 * Symbol by symbol function compare string and pattern.
 * Current position in string is p[1], in pattern is p[0].
 * 
 * @param w The wildcard pattern.
 * @param p The array containing the pointers.
 * @return Returns 1 if there is a match, 0 otherwise.
 */
static int	have_match2(const char *w, const char **p)
{
	while (*p[1])
	{
		if (p[2] != NULL && !(*p[2] + 1))
			return (1);
		if (*p[0] == *p[1] && *p[0] != '*' && p[0] && p[1])
		{
			p[0]++;
			p[1]++;
		}
		else if (*p[0] == '\\' && *(p[0] + 1) == '*' && *p[1] == '*' && p[1])
		{
			p[0] = p[0] + 2;
			p[1]++;
		}
		else if (handle_star(w, p))
			return (0);
	}
	while (*p[0] == '*' && (p[0] == w || *(p[0] - 1) != '\\'))
		p[0]++;
	return (*p[0] == '\0');
}

/**
 * @brief Checks if there is a match between string and wildcard patern.
 * 
 * This function checks if the string 's' matches the wildcard pattern 'w'.
 * The wildcard pattern can contain the '*' character, which matches any
 * sequence of characters (including an empty sequence).
 * 
 * @param s The string to be checked for a match.
 * @param w The wildcard pattern to be matched against.
 * @return Returns 1 if there is a match, 0 otherwise.
 */
static int	have_match(const char *s, const char *w)
{
	const char	*p[4];

	p[0] = w;
	p[1] = s;
	p[2] = NULL;
	p[3] = NULL;
	if ((s[0] == '.' && ft_strcmp(w, "*") == 0)
		|| ft_strcmp(w, "*.") == 0)
		return (0);
	if (ft_strcmp(w, "*") == 0)
		return (1);
	return (have_match2(w, p));
}

/**
 * Parses the word and returns a list of words that match the pattern.
 * 
 * @param word The word to parse.
 */
t_list	*parse_star(const char *word)
{
	t_list			*words;
	char			pwd[PATH_MAX];
	DIR				*dir;
	struct dirent	*s_dir;

	if (!ft_strchr(word, '*'))
		return (NULL);
	words = list_new(cmp_int, NULL, NULL);
	if (getcwd(pwd, PATH_MAX) == NULL || words == NULL)
		return (NULL);
	dir = opendir(pwd);
	if (dir == NULL)
		return (list_free(words), NULL);
	s_dir = readdir(dir);
	while (s_dir != NULL)
	{
		if (have_match(s_dir->d_name, word))
			list_put(words, (void *)L_WORD, ft_strdup(s_dir->d_name));
		s_dir = readdir(dir);
	}
	closedir(dir);
	if (list_size(words) == 0)
		return (list_free(words), NULL);
	return (words);
}
