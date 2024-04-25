# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 11:00:13 by akurochk          #+#    #+#              #
#    Updated: 2024/04/25 14:11:32 by akurochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= main.c \
	builtins/builtins_call.c \
	builtins/command_call.c \
	parser/common.c \
	utils/env.c \
	utils/error_handler.c \
	parser/executor.c \
	utils/ft_itoa.c \
	utils/ft_split.c \
	utils/ft_str.c \
	utils/ft_substr.c \
	parser/group.c \
	parser/heredoc.c \
	lexer/lexer.c \
	list/list.c \
	parser/parser_star.c \
	parser/parser.c \
	parser/pipes.c \
	utils/signal.c \
	parser/subshell.c
#	test_cmp.c
#	test_lexer.c

OBJS	= $(SRCS:.c=.o)

CC		= cc
CFLAGS	= -g3 -Wall -Werror -Wextra -I ./inc

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
