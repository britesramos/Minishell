# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sramos <sramos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 17:07:32 by sramos            #+#    #+#              #
#    Updated: 2024/09/24 10:35:41 by sramos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_PATH = ./src
SRC_FILES = $(SRC_PATH)/minishell.c\
			$(SRC_PATH)/parsing.c\
			$(SRC_PATH)/init.c
OBJ_PATH = ./obj
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC_FILES))
HEADER = include/minishell.h

CC = cc
CFLAGS = -Wall -Werror -Wextra 
OFLAGS = -lreadline -g

RM = rm -f
RD = rm -rf

all: $(NAME)

$(NAME): $(OBJ_FILES) $(HEADER) #$(LIBFT) 
	$(CC) $(SRC_FILES) $(CFLAGS) $(OFLAGS) -o $(NAME)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c $(HEADER)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ_FILES)
	$(RD) $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY = all, clean, fclean, re

