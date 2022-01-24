# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 14:48:45 by llonnrot          #+#    #+#              #
#    Updated: 2022/01/24 16:34:40 by llonnrot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nuwindow

SOURCES = test.c get_next_line.c ../libft/libft.a

FLAGS = -Wextra -Werror -Wall


all: $(NAME)

$(NAME):
	gcc $(SOURCES) -o $(NAME) $(FLAGS) -L. -lmlx -framework OpenGL -framework Appkit

fclean: 
	rm $(NAME)
