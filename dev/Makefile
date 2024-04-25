# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 11:00:13 by akurochk          #+#    #+#              #
#    Updated: 2024/04/25 10:42:13 by akurochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= main.c \
	builtins_call.c \
	command_call.c \
	common.c \
	env.c \
	error_handler.c \
	executor.c \
	ft_itoa.c \
	ft_split.c \
	ft_str.c \
	ft_substr.c \
	group.c \
	heredoc.c \
	lexer.c \
	list.c \
	parser_star.c \
	parser.c \
	pipes.c \
	signal.c \
	subshell.c
#	test_cmp.c
#	test_lexer.c

OBJS	= $(SRCS:.c=.o)

CC		= cc
CFLAGS	= -g3 -Wall -Werror -Wextra

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

test: re
	make clean
	clear
	

.PHONY: all clean fclean re
