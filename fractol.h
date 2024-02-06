/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:36:00 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/06 17:26:17 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
    int     width;
    int     height;
}			t_data;

typedef struct s_mlx_win
{
    void    *window;
    void    *mlx;
}           t_mlx_win;

typedef struct s_complex
{
    double   real;
    double   img;
    int     img_square;
}           t_complex;

typedef struct s_colors
{
    int first;
    int second;
    int third;
}           t_colors;
    
int mandelbrot(int max_iter, t_complex nb);

#endif