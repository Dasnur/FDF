# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atote <atote@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 12:44:03 by atote             #+#    #+#              #
#    Updated: 2021/01/28 17:17:01 by atote            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

MLX = ../minlibx/libmlx.a

LIB = libft/libft.a

SRC = sources/main.c \
	sources/assist.c \
	sources/draw.c \
	sources/init_mouse.c \
	sources/read_init.c \
	sources/rotate.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	gcc -o $(NAME) $(OBJ) -Llibft -lft -L ../minilibx-linux -lmlx -lGL -lm -lX11 -lXext

.c.o:
	gcc -Wall -Wextra -Werror -I includes/ -Ilibft -o $@ -c $<

$(LIB):
	cd libft && make
	cd libft && make clean

$(MLX):
	cd ../minilibx_macos && make

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)
	cd libft && make fclean
	cd ../minilibx_macos && make clean

re: fclean all