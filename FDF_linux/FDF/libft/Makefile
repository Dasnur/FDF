# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atote <atote@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/08 18:36:49 by atote             #+#    #+#              #
#    Updated: 2020/02/08 19:04:00 by atote            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_bzero.c ft_memset.c ft_strlen.c ft_putchar.c \
	   ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_itoa.c ft_strsplit.c ft_strtrim.c ft_strjoin.c \
	   ft_strsub.c ft_strequ.c ft_strnequ.c ft_memalloc.c \
	   ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	   ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	   ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	   ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	   ft_strstr.c ft_strnstr.c ft_strcmp.c ft_isupper.c \
	   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	   ft_isprint.c ft_toupper.c ft_tolower.c ft_memcpy.c \
	   ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	   ft_strncmp.c ft_atoi.c ft_lstnew.c ft_lstdelone.c \
	   ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	   get_next_line.c ft_getnbr.c free_map.c

OBJ = $(SRCS:.c=.o)

INC = libft.h

FLAGS = -Wall -Wextra -Werror -c 

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ): $(SRCS)
	gcc -c $(SRCS) -I.

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
