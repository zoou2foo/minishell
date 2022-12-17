# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjean <vjean@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 15:03:44 by vjean             #+#    #+#              #
#    Updated: 2022/12/17 15:51:03 by vjean            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#NAME_BONUS = 

SRCS = srcs/main.c \

#BONUS =

LIBFT =	libft/libft.a
RL_LIB = -L ./includes/readline -lreadline ## comme ça qu'on link une lib static
# RL_HST = lib/lib/libhistory.a

OBJS = $(SRCS:.c=.o)

CC = gcc 

CFLAGS = -Wall -Wextra -Werror

BONUS_OBJS = $(BONUS:.c=.o)

#*****INTRO*****
define intro
@bash pew_pew.sh
endef

.c.o:
		@$(CC) $(CFLAGS) -I includes -c $< -o $(<:.c=.o)

RM = rm -fr

all: $(NAME)

$(NAME): $(OBJS)
	$(call intro)
	cd libft && make
		@$(CC) $(CFLAGS) -I includes $(OBJS) $(LIBFT) -o $(NAME) $(RL_LIB) -lcurses
# quand tu utilises une librairie statique préférablement, il faut compiler à la fin. C'est la norme.		
exec: re $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppression=file.txt ./minishell

clean:
	$(RM) $(OBJS)
#	$(RM) $(BONUS_OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
#	$(RM) $(NAME_BONUS)
	$(RM) $(LIBFT)
	
re: fclean all

#bonus: $(BONUS_OBJS)
#	$(call intro)
#	cd libft && make
#		@$(CC) -I includes $(BONUS_OBJS) $(LIBFT) -o $(NAME_BONUS)

.PHONY: all clean fclean re