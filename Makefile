# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: marvin <marvin@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2024/09/23 17:07:32 by sramos        #+#    #+#                  #
#    Updated: 2024/11/21 09:16:46 by mstencel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = src

SRC_FILES = src/minishell.c\
			src/clean_up.c\
			src/init.c\
			src/expansion/expansion.c\
			src/parsing/parsing.c\
			src/parsing/input_checker.c\
			src/parsing/parse_envp.c\
			src/parsing/tokenization.c\
			src/parsing/tokenization_utils.c\
			src/parsing/parse_input.c\
			src/parsing/parse_heredoc.c\
			src/parsing/parse_input_utils.c\
			src/parsing/parsing_utils.c\
			src/parsing/error_p.c\
			src/execution/exec.c\
			src/execution/built_ins/builtins_manager.c\
			src/execution/built_ins/cd_utils.c\
			src/execution/built_ins/cd.c\
			src/execution/built_ins/echo.c\
			src/execution/built_ins/env.c\
			src/execution/built_ins/envp_utils.c\
			src/execution/built_ins/exit.c\
			src/execution/built_ins/export.c\
			src/execution/built_ins/export_print.c\
			src/execution/built_ins/pwd.c\
			src/execution/built_ins/unset.c\
			src/execution/pipes/fd_utils.c\
			src/execution/pipes/mltpl_cmd.c\
			src/execution/pipes/path.c\
			src/execution/pipes/single_cmd.c\
			src/execution/signals/signals.c

OBJ_PATH = obj

# this is a pattern substitution:
# the SRC_FILES will have a list with their full paths
# the SRC_PATH/%.c are the source of the files that will be replaced
# the OBJ_PATH/%.o are the replacement of the /%.c
OBJ_FILES = $(SRC_FILES:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

HEADER = include/minishell.h

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
# CFLAGS += -fsanitize=address
OFLAGS = -lreadline

RM = rm -f
RD = rm -rf

info-%:
	$(info $($*))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(HEADER)
	@echo "SOURCE FILES COMPILED"
	make -C $(LIBFT_PATH)
	@echo "CREATING MINISHELL"
	$(CC) $(OBJ_FILES) $(CFLAGS) $(OFLAGS) -o $(NAME) $(LIBFT)
	@echo "MINISHELL CREATED"

# the $(@D) - The directory part of the file name of the target,
# with the trailing slash removed. 
# If the value of ‘$@’ is dir/foo.o then ‘$(@D)’ is dir. 
# This value is . if ‘$@’ does not contain a slash.

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	@if [ ! -d "$(@D)" ]; then mkdir $(@D) & echo "$(@D) MADE"; fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "REMOVING OBJECT FILES"
	$(RM) $(OBJ_FILES)
	$(RD) $(OBJ_PATH)
	@echo "OBJECT FILES REMOVED"

fclean: clean
	@echo "REMOVING MINISHELL"
	$(RM) $(NAME)
	@echo "MINISHELL REMOVED"

re: fclean all

.PHONY = all, clean, fclean, re, info
