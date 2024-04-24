# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbecker <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 15:00:14 by mbecker           #+#    #+#              #
#    Updated: 2024/04/23 15:01:49 by mbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror

NAME 	= libft.a

FILES =	files/get_next_line.c

LIST  =	list/comparators.c \
		list/list_a.c \
		list/list_b.c \
		list/list_dup.c \
		list/tab_to_list.c 

STR =	strings/ft_atoi.c \
		strings/ft_is.c \
		strings/ft_len.c \
		strings/ft_split.c \
		strings/ft_strchr.c \
		strings/ft_strcmp.c \
		strings/ft_strcpy.c \
		strings/ft_strdup.c \
		strings/ft_strjoin.c \
		strings/ft_substr.c \
		strings/ft_wordcount.c \
		tab/ft_tabdup.c \
		tab/ft_tabjoin.c

OTHER =	other/freetab.c \
		other/ft_calloc.c

SRC	=	$(FILES) $(LIST) $(STR) $(OTHER)
OBJ	=	$(SRC:.c=.o)
OBJDIR	= .obj/files .obj/str .obj/other

HEADER	= libft.h
NAME	= libft.a

RED		=\033[1;31m
LRED	=\033[0;31m
GREEN	=\033[1;32m
LGREEN	=\033[0;32m
YELLOW	=\033[1;33m
LYELLOW	=\033[0;33m
GREY	=\033[1;37m
NC		=\033[0m

all: 	$(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@rm -rf $(OBJ) .obj
	@echo "$(LGREEN)libft.a ready.$(NC)"

%.o: %.c
	@mkdir -p $(OBJDIR) 
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(LRED)Cleaning libft...$(NC)"
	@rm -rf a.out libexe a.out.dSYM .vscode $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY	: all clean fclean re