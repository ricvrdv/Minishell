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

SRC_DIRS = src/init src/parse src/utils src/tokens src/builtin src/signal src/tree src/exec
SRCS = src/init/init.c \
       src/init/add.c \
       src/main.c \
       src/parse/parse.c \
       src/parse/parse.utils.c \
       src/utils/utils.c \
       src/utils/clear.c \
       src/tokens/token.utils.c \
       src/parse/quotes.c \
       src/signal/signal.c \
       src/init/prompt.c \
       src/tree/tree_parse.c \
       src/tree/tree_utils.c \
       src/tokens/tokens.c \
       src/exec/exec.c \
       src/tree/prep_tree.c \
       src/builtin/cd_utils.c \
       src/builtin/cd.c \
       src/builtin/echo.c \
       src/builtin/env.c \
       src/builtin/exit.c \
       src/builtin/exit_utils.c \
       src/builtin/export.c \
       src/builtin/export_utils.c \
       src/builtin/pwd.c \
       src/builtin/unset.c \
       src/builtin/builtin_utils.c \
       src/builtin/builtin_utils2.c \
       src/exec/exec_utils.c \
       src/exec/quotes.c \
       src/exec/exec_pipe.c \
       src/exec/exec_redir.c \
       src/exec/heredoc.c \
       src/tree/expand.c \
       src/utils/extra_utils.c \
       src/tree/expand_utils.c \
       src/exec/redirect_utils.c \
       src/utils/clear_utils.c \
       src/exec/extra_utils_exec.c \
       src/utils/more_utils.c 

OBJS = $(SRCS:.c=.o)

################################################################################
#                                  Makefile objs                               #
################################################################################

all: $(NAME)

$(NAME): $(OBJS) $(MYLIB)
	@echo "\033[0;32mCompilation Successful!\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) -L$(MYLIB_DIR) -lft -o $(NAME) 

$(MYLIB): $(MYLIB_DIR)
	@make -C $(MYLIB_DIR) -s

# Rule to compile .c files into .o files
%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJS)
	@make clean -C $(MYLIB_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(MYLIB_DIR)

re: fclean all

################################################################################
#                                  Valgrind Command                             #
################################################################################

SUPPRESSION_FILE = readline.supp

SUPPRESSION_FILE = readline.supp

valgrind: $(NAME) $(SUPPRESSION_FILE)
	@/usr/bin/valgrind --suppressions=$(SUPPRESSION_FILE) --leak-check=full -s --show-leak-kinds=definite,indirect,possible ./$(NAME) || true

run: $(NAME)
	@./$(NAME)

.PHONY: all clean fclean re valgrind run
