/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:36:00 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/07 18:42:01 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>

typedef struct s_range
{
    double  min_x;
    double  max_x;
    double  min_y;
    double  max_y;
    double  trans_y;
    double  trans_x;
}           t_range;

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
    int     width;
    int     height;
    t_range *range;
}           t_mlx_win;

typedef struct s_complex
{
    double   real;
    double   img;
}           t_complex;


typedef struct s_colors
{
    int first;
    int second;
    int third;
}           t_colors;
    
int mandelbrot(int max_iter, t_complex nb);

#endif