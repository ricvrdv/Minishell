
SRCS = \
    ft_atoi.c \
    ft_bzero.c \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isascii.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_memcpy.c \
    ft_memmove.c \
    ft_memset.c \
    ft_strchr.c \
    ft_strlcat.c \
    ft_strlcpy.c \
    ft_strlen.c \
    ft_strncmp.c \
    ft_strnstr.c \
    ft_strrchr.c \
    ft_tolower.c \
    ft_toupper.c \
    ft_strdup.c \
    ft_calloc.c \
    ft_substr.c \
    ft_strjoin.c \
    ft_strtrim.c \
    ft_putnbr_fd.c \
    ft_putendl_fd.c \
    ft_putstr_fd.c \
    ft_putchar_fd.c \
    ft_striteri.c \
    ft_strmapi.c \
    ft_split.c \
    ft_itoa.c \
    ft_printc.c \
    ft_printd.c \
    ft_printf.c \
    ft_printp.c \
    ft_prints.c \
    ft_printu.c \
    ft_printx.c \
    get_next_line.c \
    get_next_line_utils.c \
    ft_strnlen.c \
    ft_strndup.c \
    ft_str_size.c \
    ft_strcmp.c \
    ft_strcpy.c \
    space.c \
    ft_is_numeric.c
    
    
    
OBJS = $(SRCS:.c=.o)

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -fPIC

all: $(NAME)
	
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	@echo "\033[0;31mObjects removed\033[0m"
fclean: clean
	rm -f $(NAME)
	@echo "\033[0;31mLibftprintf.a removed\033[0m"
re: fclean all

notes: 
