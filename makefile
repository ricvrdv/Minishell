################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RLFLAGS = -lreadline

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

vpath %.h includes
vpath %.c src

MYLIB_DIR = ./inc/Mylib/
MYLIB = ./inc/Mylib/libft.a

SRCS = main.c \
       utils.c \
	   init.c

OBJS = $(addprefix src/, $(SRCS:.c=.o))

################################################################################
#                                  Makefile objs                               #
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0;32mCompilation Successful!\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) $(MYLIB) -o $(NAME) -s

$(MYLIB): $(MYLIB_DIR)
	@make -C $(MYLIB_DIR) -s

src/%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re