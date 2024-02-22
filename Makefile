# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 12:11:49 by kipouliq          #+#    #+#              #
#    Updated: 2024/02/22 15:43:32 by kipouliq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCS = ./srcs/main.c \
		./srcs/fractals_calc.c \
		./srcs/rgb.c \
		./srcs/color_manipulation.c \
		./srcs/normalization_conversion.c \
		./srcs/mlx_display_functions.c \
		./srcs/alloc_free.c \
		./srcs/zoom_mouse_inputs.c \
		./srcs/keyboard_inputs.c \
		./srcs/math_stuff.c \
		./srcs/color_palettes.c \
		./srcs/args_parsing.c \
		./srcs/utils.c

OBJ = $(SRCS:.c=.o)

CC = cc

INCLUDE = -I

FLAGS = -Wall -Wextra -Werror 

PATH_MLX = ./minilibx-linux

PATH_LIBFT = ./megalibft

NEW_PATH_LIBFT = .

LIBFT = ./megalibft/megalibft.a

MLX = ./minilibx-linux/libmlx.a

MLX_FLAGS = -lmlx -lXext -lX11 -lm 

all : $(NAME)

$(NAME) : $(OBJ)
	make -C $(PATH_LIBFT)
	make -C $(PATH_MLX)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -L ./minilibx-linux $(MLX_FLAGS) -o $(NAME) -g3 -O2

%.o:%.c
	$(CC) $(FLAGS) -I $(PATH_LIBFT) -I $(PATH_MLX) -c $< -o $@

clean :
	make -C $(PATH_LIBFT) clean
	make -C $(PATH_MLX) clean
	rm -f *o

fclean : clean
	make -C $(PATH_LIBFT) fclean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re