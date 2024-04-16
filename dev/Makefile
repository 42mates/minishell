# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 11:00:13 by akurochk          #+#    #+#              #
#    Updated: 2024/04/11 11:40:13 by akurochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= main.c \
		ft_str.c

OBJS	= $(SRCS:.c=.o)

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $<  -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re