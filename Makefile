# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbecker <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 13:23:43 by mbecker           #+#    #+#              #
#    Updated: 2024/04/15 17:09:01 by mbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = 	main.c \
		src/execute.c \
		src/set_home_path.c \
		src/here_doc.c \
		src/pipex.c

all: $(NAME)

$(NAME): libft
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) -Llibft -lft
	@echo "$(LGREEN)./$(GREEN)$(NAME)$(LGREEN) ready.$(NC)"

clean:
	@echo "$(LRED)Removing objects and misc...$(NC)"
	@rm -rf *.out* */*.out testexe *.dSYM* .vscode

fclean: clean
	@rm -f $(NAME)
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

tester: all
	@if [ ! -d "pipex.tester" ]; then \
		echo "$(GREEN)Cloning tester...$(LGREEN)"; \
		git clone https://github.com/vfurmane/pipex-tester pipex.tester; \
	fi
	@chmod +x pipex.tester/run.sh
	@echo "$(YELLOW)Tester ready.$(NC)"
	@echo "$(RED)Running tester...$(NC)"
	@printf "..\nn" | pipex.tester/run.sh
	
