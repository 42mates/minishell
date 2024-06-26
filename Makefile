# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 13:23:43 by mbecker           #+#    #+#              #
#    Updated: 2024/05/31 17:01:34 by akurochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = 	src/main.c \
		\
		src/builtins/ft_echo.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_pwd.c \
		src/builtins/ft_export.c \
		src/builtins/ft_unset.c \
		src/builtins/ft_env.c \
		src/builtins/ft_exit.c \
		src/builtins/builtin_utils.c \
		src/builtins/builtins_call.c \
		src/builtins/command_call.c \
		\
		src/lexer/lexer.c \
		src/lexer/lexer2.c \
		\
		src/parser/common.c \
		src/parser/executor.c \
		src/parser/group.c \
		src/parser/heredoc.c \
		src/parser/parser_dollar.c \
		src/parser/parser_groups.c \
		src/parser/parser_handle_tokens.c \
		src/parser/parser_manage_group.c \
		src/parser/parser_manage_group2.c \
		src/parser/parser_star.c \
		src/parser/parser_token_field.c \
		src/parser/parser_token.c \
		src/parser/parser_utils.c \
		src/parser/parser.c \
		src/parser/pipes.c \
		src/parser/subshell.c \
		\
		src/utils/error_handler.c \
		src/utils/fd_utils.c \
		src/utils/ft_str_split.c \
		src/utils/ft_str_concat.c \
		src/utils/filetype.c \
		src/utils/handle_env.c \
		src/utils/signal.c \
		src/utils/env.c

all: $(NAME)

$(NAME): libft
	@if [ ! -f minishell ]; \
		then $(CC) $(CFLAGS) -o $(NAME) $(SRC) -Llibft -lft -lreadline;\
		echo "$(LGREEN)./$(GREEN)$(NAME)$(LGREEN) ready.$(NC)";\
	else\
		echo "$(LGREEN)./$(GREEN)$(NAME)$(LGREEN) already compiled.$(NC)";\
	fi

bonus: libft
	@if [ ! -f minishell_bonus ]; \
		then $(CC) $(CFLAGS) -o $(NAME)_bonus $(SRC) -Llibft -lft -lreadline;\
		echo "$(LGREEN)./$(GREEN)$(NAME)_bonus$(LGREEN) ready.$(NC)";\
	else\
		echo "$(LGREEN)./$(GREEN)$(NAME)_bonus$(LGREEN) already compiled.$(NC)";\
	fi

clean:
	@echo "$(LRED)Removing objects and misc...$(NC)"
	@rm -rf *.out* */*.out testexe *.dSYM* .vscode

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean
	@echo "$(RED)FULL CLEAN FINISHED$(NC)"

re: fclean all

libft:
	@if [ ! -f libft/libft.a ]; then make -C ./libft all; fi

.PHONY : all clean fclean re libft

RED =\033[1;31m
LRED =\033[0;31m
GREEN =\033[1;32m
LGREEN =\033[0;32m
YELLOW =\033[1;33m
LYELLOW =\033[0;33m
GREY =\033[1;37m
NC =\033[0m

f: libft
	@$(CC) -g -o $(NAME) $(SRC) -Llibft -lft
	@echo "$(LGREEN)./$(GREEN)$(NAME)$(LGREEN) ready.$(NC)"

TEST = test.c src/parser/set_path2.c

test: libft
	@$(CC) -g -o test $(TEST) -Llibft -lft -lreadline
	@echo "$(LGREEN)./$(RED)test$(LGREEN) ready.$(NC)"

tester: re
	@if [ ! -d minishell_tester ]; then git clone https://github.com/LucasKuhn/minishell_tester.git; fi
	@cd minishell_tester && ./tester #| grep -v "✅"