# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 14:48:45 by llonnrot          #+#    #+#              #
#    Updated: 2022/02/04 16:43:19 by llonnrot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SOURCES = test.c func.c libft/libft.a

FLAGS = -Wextra -Werror -Wall

INCLUDES = fdf.h

all: $(NAME)

$(NAME):
	gcc $(SOURCES) -I $(INCLUDES) -o $(NAME) $(FLAGS) -L. -lmlx -framework OpenGL -framework Appkit

fclean: 
	rm $(NAME)
