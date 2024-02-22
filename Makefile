# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 12:11:49 by kipouliq          #+#    #+#              #
#    Updated: 2024/02/22 15:14:05 by kipouliq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCS = ./main.c \
		./fractals_calc.c \
		./rgb.c \
		./color_manipulation.c \
		./normalization_conversion.c \
		./mlx_display_functions.c \
		./alloc_free.c \
		./zoom_mouse_inputs.c \
		./keyboard_inputs.c \
		./math_stuff.c \
		./color_palettes.c \
		./args_parsing.c \
		./utils.c

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
	# make -C $(PATH_MLX) fclean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re