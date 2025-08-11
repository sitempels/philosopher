# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    stempels_Makefile                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stempels <stempels@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/03/20 12:11:32 by stempels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
#MAKEFLAGS += --silent
#
NAME = push_swap 
TYPE = EXEC
#----------------------------COMPILER------------------------------------------#
CC = clang
CCFLAGS = -Wall -Wextra -Werror -g
CPPFLAGS = $(INC_FLAG)
#
#----------------------------LINKER--------------------------------------------#
#----------------------------DEBUG---------------------------------------------#
#----------------------------MAIN----------------------------------------------#
#----------------------------SRC-----------------------------------------------#
SRC_DIR = src
SRC = $(addprefix src/, $(addsuffix .c, main_push_swap push_swap push_swap_utils push_swap_utils2 manip_push manip_swap manip_rotate manip_rrotate)) 
#
#----------------------------OBJ-----------------------------------------------#
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
#
#----------------------------LIB-----------------------------------------------#
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_FLAG = -I $(LIBFT_DIR)/$(INC_DIR)
#
#----------------------------HEADER--------------------------------------------#
INC_DIR = include
INC_FLAG += -I$(INC_DIR)
#
#----------------------------RULES---------------------------------------------#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -c $< -o $@
#
lib:	$(LIBFT) 
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $@
	@echo "$(NAME) $(GREEN)created !$(NC)"
#
clean:
	rm -rf $(OBJ_DIR)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
libclean:
	$(MAKE) clean -C $(LIBFT_DIR)	
	rm -rf $(LIBFT)
#
fclean: clean
	rm -rf $(NAME)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
ffclean: fclean libclean
#
re: ffclean all
#
.PHONY: all clean libclean fclean ffclean re design
#----------------------------TEXT----------------------------------------------#
GREEN=\033[0;32m
NC=\033[0m
#
#----------------------------MISC----------------------------------------------#
#
