# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/08/14 16:27:01 by stempels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += --silent
#
NAME_PROJECT = philosopher 
NAME = $(NAME_PROJECT)
debug: NAME = $(addprefix debug_, $(NAME_PROJECT))
TYPE = EXEC
#----------------------------COMPILER------------------------------------------#
CC = cc
debug: CC = gcc 
CCFLAGS = -Wall -Wextra -Werror
debug: CCFLAGS = -g3
CPPFLAGS = $(INC_FLAG)
#
#----------------------------LINKER--------------------------------------------#
#----------------------------DEBUG---------------------------------------------#
#----------------------------HEADER--------------------------------------------#
INC_DIR = inc
INC_FLAG = -I$(INC_DIR)
#
#----------------------------SRC-----------------------------------------------#
SRC_DIR = src
#
SRCS = main philosopher philosopher_utils 
#
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS))) 
#
#----------------------------OBJ-----------------------------------------------#
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
#
#----------------------------MISC----------------------------------------------#
DEPENDS = $(patsubst %.c, %.d, $(SRC))
#
#----------------------------RULES---------------------------------------------#
#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@
#
lib:	$(LIBFT) 
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
$(NAME): $(OBJ) 
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) $(GREEN)created !$(NC)"

run: $(NAME)
	@./$(NAME)
#
leak: debug
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --track-fds=yes --suppressions=./valgrind.supp ./debug_$(NAME_PROJECT)
#
vgdb: debug
	@valgrind --vgdb-error=0 --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=./valgrind.supp ./debug_$(NAME_PROJECT)
#
clean:
	rm -rf $(OBJ_DIR) $(DEPENDS)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
fclean: clean
	rm -rf $(NAME)
	rm -rf $(addprefix debug_, $(NAME))
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
ffclean: fclean
#
re: ffclean all
#
debug: $(OBJ) 
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) created !"
#
-include $(DEPENDS)
#
.PHONY: all clean libclean fclean ffclean re
#----------------------------TEXT----------------------------------------------#

#
#----------------------------MISC----------------------------------------------#
#
