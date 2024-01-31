# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 12:11:49 by kipouliq          #+#    #+#              #
#    Updated: 2024/01/31 13:38:27 by kipouliq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = ./main.c \
		./mandelbrot.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3

PATH_MLX = ./minilibx-linux

PATH_LIBFT = ./megalibft

NEW_PATH_LIBFT = .

LIBFT = ./megalibft/megalibft.a

MLX_OPT = -lmlx -lXext

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux $(SRC) -L /usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus : $(BONUS_OBJS)
	make -C $(PATH_LIBFT)
	$(CC) $(FLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME_BONUS) -g3 

%.o:%.c
	$(CC) $(FLAGS) -I $(PATH_LIBFT) -c $<  -o $@

clean :
	make -sC $(PATH_LIBFT) clean
	rm -f *o

fclean : clean
	make -sC $(PATH_LIBFT) fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re : fclean
	make all

.PHONY : all bonus clean fclean re