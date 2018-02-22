# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gficara <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:25:41 by gficara           #+#    #+#              #
#    Updated: 2018/02/22 19:12:50 by gficara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gficara.filler

VIS = visualizer

LIB = filler.a

LIB2 = libftprintf/libftprintf.a

FLAGS = -Wall -Wextra -Werror -g

CC = gcc

INC = -I includes

SRC = sources/piece.c \
		sources/heatmap.c \
		sources/main.c

SRC2 =  sources/graf.c

OBJ = $(SRC:.c=.o)

OBJ2 = $(SRC2:.c=.o)

all : $(VIS)

$(NAME) : $(OBJ) Makefile
	@make -C libftprintf
	@ar rc $(LIB) $(OBJ)
	@ranlib $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(LIB) $(LIB2)
	@echo "Creating $(NAME)"

$(VIS) : $(OBJ2) $(NAME) Makefile
	@$(CC) $(FLAGS) -o $(VIS) $(LIB) $(LIB2) $(OBJ2)
	@echo "Creating $(VIS)"

%.o: %.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean :
	@make clean -C libftprintf
	@rm -rf $(OBJ) $(OBJ2)
	@echo "Removing $(NAME) objects"

fclean : clean
	@make fclean -C libftprintf
	@rm -rf $(NAME) $(LIB) $(VIS)
	@echo "Removing $(LIB), $(VIS) and $(NAME)"

re: fclean all
