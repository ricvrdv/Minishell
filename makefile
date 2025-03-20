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

MYLIB_DIR = ./inc/Mylib/
MYLIB = ./inc/Mylib/libft.a

SRC_DIRS = src/init src/parse src/utils
SRCS = src/init/init.c \
       src/init/add.c \
       src/init/main.c \
       src/parse/parse.c \
       src/parse/parse.utils.c \
       src/utils/utils.c \
	   src/utils/clear.c \
	   src/tokens/token.utils.c

OBJS = $(SRCS:.c=.o)

################################################################################
#                                  Makefile objs                               #
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0;32mCompilation Successful!\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) $(MYLIB) -o $(NAME) 

$(MYLIB): $(MYLIB_DIR)
	@make -C $(MYLIB_DIR) -s

# Rule to compile .c files into .o files
src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

################################################################################
#                                  Valgrind Command                             #
################################################################################

VALGRIND = valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes

run: $(NAME)
	@$(VALGRIND) ./$(NAME) || true

.PHONY: all clean fclean re
