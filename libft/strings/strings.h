/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:48:31 by mbecker           #+#    #+#             */
/*   Updated: 2024/04/25 19:33:08 by mbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# include "../libft.h"

size_t	ft_strlen(const char *s);
size_t	ft_tablen(const char **tab);
// ft_len.c

int		ft_atoi(const char *str);
// ft_atoi.c

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
// ft_is.c

char	*ft_itoa(int n);
// ft_itoa.c

char	**ft_split(char const *s, char c);
char	**ft_split_charset(char const *s, char *charset);
// ft_split.c

char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strchrset(char *s, char *set);
// ft_strchr.c

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// ft_strcmp.c

char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
// ft_strcpy.c

char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *src, size_t size);
// ft_strdup.c

char	*ft_strjoin(char *s1, char *s2, int free_s1, int free_s2);
// ft_strjoin.c

char	*ft_substr(char const *s, unsigned int start, size_t len);
// ft_substr.c

size_t	ft_wordcount(const char *str, char sep);
size_t	ft_wordcount_cset(const char *str, char *charset);
// ft_wordcount.c

#endif
