/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:36:00 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/14 14:44:09 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WHEELUP 4
# define WHEELDOWN 5
# define DOWN_ARROW 65364
# define PLUS 61
# define MINUS 45

# include <stdio.h>

typedef struct s_complex
{
	double		real;
	double		img;
}				t_complex;

typedef struct s_range
{
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
	double		trans_y;
	double		trans_x;
	int			max_iter;
	t_complex	c_plot;
}				t_range;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef struct s_mlx_win
{
	void		*window;
	void		*mlx;
	int			width;
	int			height;
	t_range		*range;
}				t_mlx_win;

typedef struct s_colors
{
	int			r;
	int			g;
	int			b;
}				t_colors;

int				mandelbrot(int max_iter, t_complex nb);
int             mandelbrot2(t_complex px, int max_iter);
int				julia(int max_iter, t_complex nb, t_complex c_plot);

#endif