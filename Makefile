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
.PHONY: all bonus clean clear fclean fclear re run rerun pewpew leaks ldirs

#------------------------------------------------------------------------------#
#                                    FLAGS                                     #
#------------------------------------------------------------------------------#

# Hide calls
export VERBOSE = FALSE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

# Debug mode
export DEBUG = TRUE
ifeq ($(DEBUG),TRUE)
	MODE = -g
else
	MODE =
endif

# Start screen mode
export GRAPHIC = FALSE
ifeq ($(GRAPHIC),TRUE)
	START = bash pew_pew2.sh
else
	START =
endif

#------------------------------------------------------------------------------#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf
MD		=	mkdir -p
INCLUDE =	-I includes

# Program and directory names
NAME	=	minishell
SRCDIR	=	src/
OBJDIR	=	bin/
TSTDIR	=	tests/

# File names (including their subdirectory if needed)
FILES	=	main \
			built-ins/cd \
			built-ins/env \
			built-ins/exit \
			built-ins/export \
			built-ins/pwd \
			built-ins/unset \
			built-ins/echo \
			parsing/tokenizer \
			parsing/token_handler \
			parsing/expander \
			parsing/parser \
			parsing/converter \
			executor/system_cmds \
			executor/here_doc \
			executor/pre_execution \
			executor/utils_to_exec \
			signals/signals

# Libraries (.a files) to include for compilation
LIBFT	=	./libft/libft.a
LIBRL	=	-L ./includes/readline/ -lreadline -lcurses

SRCS	=	$(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))

# Default command to call when using make run or make leaks
CMD		=	./minishell

#------------------------------------------------------------------------------#
#                                   TARGETS                                    #
#------------------------------------------------------------------------------#

all: ldirs $(NAME)

# Creates the object directories and subdirectories
ldirs:
	$(HIDE) $(MD) $(OBJDIR)
	$(HIDE) $(MD) $(OBJDIR)/built-ins
	$(HIDE) $(MD) $(OBJDIR)/parsing
	$(HIDE) $(MD) $(OBJDIR)/executor
	$(HIDE) $(MD) $(OBJDIR)/signals

$(NAME): $(OBJS)
	$(HIDE) $(START)
	$(HIDE) cd libft && make && cd ..
	$(HIDE) $(CC) $(MODE) $(CFLAGS) $(INCLUDE) $(LIBFT) -o $@ $^ $(LIBRL)
	@echo "$(GREEN)Files compiled$(DEF_COLOR)"

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -c $< -o $@ $(INCLUDE)

# Removes objects
clear: clean
clean:
	$(HIDE) $(RM) $(OBJS)
	$(HIDE) $(RM) $(NAME).dSYM
	@echo "$(MAGENTA)Object files cleaned$(DEF_COLOR)"

# Removes object dir and executable
fclear: fclean
fclean: clean
	$(HIDE) $(RM) $(OBJDIR)
	$(HIDE) cd libft && make fclean && cd ..
	@echo "$(MAGENTA)Object directory cleaned$(DEF_COLOR)"
	$(HIDE) $(RM) $(NAME)
	@echo "$(RED)Executable cleaned$(DEF_COLOR)"

# Removes object dir and executable and remakes everything
re: fclean all
	@echo "$(CYAN)Cleaned and rebuilt everything!$(DEF_COLOR)"

# Display start scrren
pewpew:
	$(HIDE) bash pew_pew2.sh

# Runs the program NEED TO BE FIXED
rerun: re run
run: all
	$(HIDE) $(CMD)

# Runs the program with valgrind
leaks: all
	@echo "$(RED)Checking leaks...$(DEF_COLOR)"
	$(HIDE) valgrind --show-leak-kinds=all --trace-children=yes --leak-check=full --track-fds=yes --suppressions=supp.txt $(CMD)
