# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 18:14:19 by marvin            #+#    #+#              #
#    Updated: 2025/09/22 18:14:19 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC=gcc
CFLAGS=-Wall -Werror -Wextra -Iinclude -g #-fsanitize=address

LIBFT_PATH = include/libft

LIBFT = $(LIBFT_PATH)/libft.a

NAME = conchita
SRC = src/main.c\
src/lexer/lexer.c src/lexer/lexer_utils.c\
src/parser/parser.c\
src/execution/execution_utils.c src/execution/environment.c src/execution/command.c\
src/built_in/cd.c src/built_in/echo.c src/built_in/pwd.c\
src/loop_parser_execution.c

OBJ = $(SRC:.c=.o)

HEADER = includes/minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_PATH) 
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"
%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@
	@echo "$(NAME): $(GREEN)$(OBJ) was created$(RESET)"
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "$(NAME): $(GREEN)$(LIBFT) was created$(RESET)"
clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -f $(OBJ)
	@echo "$(NAME): $(RED)$(OBJ) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
re: fclean all

.PHONY: all clean fclean re