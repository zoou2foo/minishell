# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjean <vjean@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 11:22:54 by vjean             #+#    #+#              #
#    Updated: 2022/12/08 11:27:05 by vjean            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#NAME_BONUS = minishell_bonus

SRCS = srcs/main.c \

#BONUS =  \

LIBFT =	libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc 

CFLAGS = -Wall -Wextra -Werror

#BONUS_OBJS = $(BONUS:.c=.o)

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
		@$(CC) $(CFLAGS) -I includes $(OBJS) $(LIBFT)  -o $(NAME)
		
exec: re $(NAME)
	valgrind --leak-check=yes --trace-children=yes --track-fds=yes ./minishell

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