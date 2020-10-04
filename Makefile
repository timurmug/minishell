# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 15:03:36 by qtamaril          #+#    #+#              #
#    Updated: 2020/10/04 12:40:46 by qtamaril         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_A =	libft/libft.a
GNL_A = gnl/gnl.a
INCLUDE = includes/minishell.h

FLAGS_W = -Wall -Wextra -Werror
FLAGS_LIB = -Iincludes

DIR_SRCS = srcs
DIR_LIB = libft
DIR_INC = includes
DIR_GNL = gnl

SRCS = srcs/commands.c \
		srcs/env.c \
		srcs/exit.c \
		srcs/main_utils.c \
		srcs/main.c
OBJS = $(SRCS:%.c=%.o)

.PHONY: all clean fclean re norme run

all: $(NAME)

$(NAME): $(INCLUDE) $(OBJS)
	@make -C $(DIR_GNL)
	@make -C $(DIR_LIB)
	@make bonus -C $(DIR_LIB)
	gcc $(FLAGS_W) $(LIB_A) $(GNL_A) $(OBJS) -o $(NAME)

norme:
	@make fclean
	@echo
	norminette ./$(DIR_GNL)/
	@echo
	norminette ./$(DIR_INC)
	@echo
	norminette ./$(DIR_LIB)
	@echo
	norminette ./$(DIR_SRCS)

%.o: %.c
	gcc -c $(FLAGS_LIB) $(FLAGS_W) -o $@ $<

clean:
	rm -rf $(OBJS)
	@make -C $(DIR_GNL) clean
	@make -C $(DIR_LIB) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(GNL_A)
	@make -C $(DIR_LIB) fclean

re: fclean all
