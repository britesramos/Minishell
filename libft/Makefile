.PHONY:	all clean fclean re

SRCFILES = ft_atoi.c\
ft_atol.c\
ft_bzero.c\
ft_calloc.c\
ft_free.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_itoa.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memmove.c\
ft_memset.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_striteri.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strmapi.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\
ft_printf_extra.c\
ft_printf.c\
get_next_line.c

OBJFILES = $(SRCFILES:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
ARFLAGS = -r -c -s
HEADER = libft.h
NAME = libft.a
RM = rm -f

all: $(NAME)

$(NAME): $(OBJFILES)
	@echo "SOURCE FILES COMPILED"
	@echo "CREATING LIBFT"
	ar $(ARFLAGS) $(NAME) $(OBJFILES)
	@echo "LIBFT CREATED"

# `$<' is the automatic variable that holds the name of the dependency and
# `$@' is the automatic variable that holds the name of the target
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "REMOVING OBJECT FILES"
	$(RM) $(OBJFILES)
	@echo "OBJECT FILES REMOVED"

fclean: clean
	@echo "REMOVING LIBFT"
	$(RM) $(NAME)
	@echo "LIBFT REMOVED"

re: fclean all