# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 14:48:45 by llonnrot          #+#    #+#              #
#    Updated: 2022/02/07 15:25:11 by llonnrot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SOURCES = main.c tools.c init.c draw_01.c draw_02.c func_01.c func_02.c

FLAGS = -Wextra -Werror -Wall

LIBFT = -L libft -lft

all: $(NAME)

$(NAME):
	@echo "Compiling..."
	@make -C libft
	@gcc $(FLAGS) $(SOURCES) -o $(NAME) -I libft $(LIBFT) -L. -lmlx -framework OpenGL -framework Appkit

clean:
	@echo "Cleaning object files..."
	@make -C libft clean

fclean: clean
	@echo "Cleaning binary..."
	@make -C libft fclean
	@rm $(NAME)

re: fclean all