# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 22:00:39 by akoropet          #+#    #+#              #
#    Updated: 2019/09/17 19:00:54 by akoropet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			lem_in

SRC_DIR = 		./source/
OBJ_DIR = 		./objective/
INC_DIR = 		./include/

SRC =			main.c \
				parcer.c \
				rooms.c \
				bfs.c \
				links.c \
				ways.c \
				output.c \
				moves.c \
				flags.c

OBJ = 			$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB = 			./lib/lib.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C lib
	@gcc $(FLAGS) $(addprefix $(SRC_DIR), $(SRC)) $(LIB) -o $(NAME)
	@echo "\033[92m>>>lem_in compiled<<<\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@make clean -C lib
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C lib
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)
