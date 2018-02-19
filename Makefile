# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gficara <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:25:41 by gficara           #+#    #+#              #
#    Updated: 2018/02/17 16:17:32 by gficara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gficara.filler

LIB = filler.a

LIB2 = libftprintf/libftprintf.a

FLAGS = -Wall -Wextra -Werror -g

CC = gcc

INC = -I includes

SRC =  sources/main.c \
		sources/piece.c \
		sources/heatmap.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) Makefile
	@make -C libftprintf
	@ar rc $(LIB) $(OBJ)
	@ranlib $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(LIB) $(LIB2)
	@echo "Creating $(NAME)"

%.o: %.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean :
	@make clean -C libftprintf
	@rm -rf $(OBJ) $(LIB)
	@echo "Removing $(NAME) objects"

fclean : clean
	@make fclean -C libftprintf
	@rm -rf $(NAME) $(LIB)
	@echo "Removing $(LIB) and $(NAME)"

re: fclean all
