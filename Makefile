# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 12:11:49 by kipouliq          #+#    #+#              #
#    Updated: 2024/02/21 18:10:45 by kipouliq         ###   ########.fr        #
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
		./utils.c \
		./utils2.c

OBJ = $(SRC:.c=.o)

CC = cc

INCLUDE = -I

FLAGS = -Wall -Wextra -Werror -g3

PATH_MLX = ./minilibx-linux

PATH_LIBFT = ./megalibft

NEW_PATH_LIBFT = .

LIBFT = ./megalibft/megalibft.a

MLX_FLAGS = -lmlx -lXext -lX11 -lm

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(INCLUDE) $(OBJ) $(PATH_MLX) $(SRCS) -L ./minilibx-linux/ $(MLX_FLAGS) -o $(NAME)

bonus : $(BONUS_OBJS)
	make -C $(PATH_LIBFT)
	$(CC) $(FLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME_BONUS) -g3 

%.o:%.c
	$(CC) $(FLAGS) -I $(PATH_LIBFT) -c $< -o $@

clean :
	# make -sC $(PATH_LIBFT) clean
	rm -f *o

fclean : clean
	# make -sC $(PATH_LIBFT) fclean
	rm -f $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re