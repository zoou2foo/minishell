#------------------------------------------------------------------------------#
#                                   COLOURS                                    #
#------------------------------------------------------------------------------#

DEF_COLOR = \033[0;39m
NC		= \e[0;39m
MAGENTA	= \033[0;95m
LMAGENTA = \e[95m
RED		= \033[0;91m
LRED	= \e[91m
YELLOW	= \033[0;93m
LYELLOW	= \e[93
GREEN	= \033[0;92m
LGREEN	= \e[92m
CYAN	= \033[0;96m
LCYAN	= \e[96m
BLUE	= \033[0;94m
GRAY	= \033[0;90m
WHITE	= \033[0;97m
#------------------------------------------------------------------------------#
#                                   GENERICS                                   #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re run debug leaks tests

# Hide calls
export VERBOSE = FALSE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

# Debug mode
export DEBUG = FALSE
ifeq ($(DEBUG),TRUE)
	MODE = -g
else
	MODE =
endif

#------------------------------------------------------------------------------#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf
INCLUDE =	-I includes

# Program and directory names
NAME	=	minishell
SRCDIR	=	src/
OBJDIR	=	bin/
TSTDIR	=	tests/

# File names
FILES	=	main \
			built-ins/cd \
			built-ins/env \
			built-ins/exit \
			built-ins/export \
			built-ins/pwd \
			built-ins/unset

LIBFT	=	./libft/libft.a
LIBRL	=	-L ./includes/readline/ -lreadline -lcurses

SRCS	=	$(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))

CMD		=	./minishell

#------------------------------------------------------------------------------#
#                                   TARGETS                                    #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(HIDE) bash pew_pew2.sh
	$(HIDE) cd libft && make && cd ..
	$(HIDE) $(CC) $(MODE) $(CFLAGS) $(INCLUDE) $(LIBFT) -o $@ $^ $(LIBRL)
	@echo "$(GREEN)Files compiled$(DEF_COLOR)"


$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJDIR):
	$(HIDE) mkdir -p $(OBJDIR)

# Removes objects
clean:
	$(HIDE) $(RM) $(OBJS)
	@echo "$(MAGENTA)Object files cleaned$(DEF_COLOR)"

# Removes objects and executables
fclean: clean
	$(HIDE) $(RM) $(NAME)
	@echo "$(RED)Executable files cleaned$(DEF_COLOR)"

# Removes objects and executables and remakes
re: fclean all
	@echo "$(CYAN)Cleaned and rebuilt everything!$(DEF_COLOR)"

pewpew:
	$(HIDE) bash pew_pew2.sh

# Runs the resulting file
run: all
	$(HIDE) $(CMD)

leaks: all
	@echo "$(RED)Checking leaks...$(DEF_COLOR)"
	$(HIDE) valgrind --leak-check=full --show-leak-kinds=all --suppression=file.txt --trace-children=yes -s $(CMD)
