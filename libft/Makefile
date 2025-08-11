# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stempels <stempels@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/03/24 15:04:47 by stempels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------MAKEFILE-------------------------------------#
MAKEFLAGS += --silent

#---------------------------------COMPILER-------------------------------------#
CC = cc
CPPFLAGS = $(INC_FLAG)
CCFLAGS = -Wall -Wextra -Werror -g

#-----------------------------------SRC----------------------------------------#
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/ft_, $(addsuffix .c, isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy memmove strlcpy strlcat toupper tolower strchr strrchr strncmp memchr memcmp strnstr atoi calloc strdup substr strjoin strtrim split itoa strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear lstiter putnbr_bfd putunbr_bfd printf_fd printf_utils_fd abs isspace))

#-----------------------------------OBJ----------------------------------------#
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

#----------------------------------HEADER--------------------------------------#
INC_DIR = include
INC_FLAG = -I$(INC_DIR)

#----------------------------------RULES---------------------------------------#
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating $(NAME)"
	ar rcs $(NAME) $(OBJ)
	@echo "$(NAME) $(GREEN)created !$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@echo "$(NAME) $(GREEN)cleaned !$(NC)"

fclean: clean
	rm -rf $(NAME)
	@echo "$(NAME) $(GREEN)fcleaned !$(NC)"

re: fclean all

.PHONY: all clean fclean re

#----------------------------------TEXT----------------------------------------#
GREEN=\033[0;32m
NC=\033[0m
