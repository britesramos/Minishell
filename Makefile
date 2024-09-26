# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstencel <mstencel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 17:07:32 by sramos            #+#    #+#              #
#    Updated: 2024/09/26 19:02:25 by mstencel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = src

SRC_FILES = src/minishell.c\
			src/clean_up.c\
			src/init.c\
			src/parsing/parsing.c\
			src/parsing/invalid_input.c\
			src/parsing/parse_envp.c\
			src/parsing/parsing_utils.c\
			src/parsing/error_p.c\
			src/execution/exec.c\
			src/execution/token/token.c\
			src/execution/token/token_check.c\
			src/execution/built_ins/cd.c\
			src/execution/built_ins/echo.c\
			src/execution/built_ins/exit.c\
			src/execution/built_ins/pwd.c

OBJ_PATH = obj

# this is a pattern substitution:
# the SRC_FILES will have a list with their full paths
# the SRC_PATH/%.c are the source of the files that will be replaced
# the OBJ_PATH/%.o are the replacement of the /%.c
OBJ_FILES = $(SRC_FILES:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

HEADER = include/minishell.h

CC = cc
CFLAGS = -Wall -Werror -Wextra 
OFLAGS = -lreadline -g

RM = rm -f
RD = rm -rf

info-%:
	$(info $($*))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(HEADER)
	$(CC) $(OBJ_FILES) $(CFLAGS) $(OFLAGS) -o $(NAME)

# the $(@D) - The directory part of the file name of the target,
# with the trailing slash removed. 
# If the value of ‘$@’ is dir/foo.o then ‘$(@D)’ is dir. 
# This value is . if ‘$@’ does not contain a slash.
$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ_FILES)
	$(RD) $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY = all, clean, fclean, re, info
