# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 22:00:39 by akoropet          #+#    #+#              #
#    Updated: 2019/03/07 22:02:56 by akoropet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

SRC = main.c

LIB = ./lib/lib.a

OB = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra
# FLAGS = -Weverything

all: $(NAME)

$(NAME): $(OB)
	@make -C lib
	@gcc $(FLAGS) $(SRC) -o $(NAME) $(LIB)
	@echo "\033[95m>>>lem_in done<<\033[0m"

%.o : %.c
	@gcc $(FLAGS) -c -o  $@ $<

clean:
	@make clean -C lib
	@rm -f $(OB)

fclean: clean
	@make fclean -C lib
	@rm -f $(NAME)

re: fclean all