# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 11:00:13 by akurochk          #+#    #+#              #
#    Updated: 2024/04/29 14:27:18 by akurochk         ###   ########.fr        #
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
	parser/parser_groups.c \
	utils/ft_itoa.c \
	utils/ft_split.c \
	utils/ft_str.c \
	utils/ft_strdup.c \
	utils/ft_substr.c \
	utils/ft_str_concat.c \
	utils/ft_str_split.c \
	parser/group.c \
	parser/heredoc.c \
	lexer/lexer.c \
	lexer/lexer2.c \
	list/list.c \
	list/list2.c \
	list/list3.c \
	parser/parser_star.c \
	parser/parser.c \
	parser/pipes.c \
	utils/signal.c \
	parser/subshell.c \
	tests/test_builtins.c
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
