/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:36:00 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/22 15:13:50 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define ESCAPE 65307
# define WHEELUP 4
# define WHEELDOWN 5
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define I 105
# define O 111
# define Y 121
# define U 117
# define P 112
# define C 99
# define R 114
# define PLUS 61
# define MINUS 45
# define KEY_0 48
# include "./megalibft/megalibft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>

typedef int		(*t_fractal_func)();

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
	double		trans_x;
	double		trans_y;
	int			max_iter;
	int			colors_palette;
	int			colors_idx;
	int			fractal;
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

int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

t_data			*create_image(t_mlx_win *data);
int				*create_color_segments(int palette_nb);
int				*color_shift(int *colors_segments, int index);
void			color_gradient_px_put(t_data *img, double **px_iter_tab,
					int *colors);
t_complex		pixel_to_complex(int x, int y, t_mlx_win *data, t_range *range);
double			normalize_value(double value, double min, double max);
void			normalize_data(double **data, int height, int width);

void			my_mlx_px_put(t_data *img, int x, int y, int color);
int				init_fractal_img(t_mlx_win *data, t_range *range);

double			**ft_alloc_tab_double(int width, int height);
int				*ft_free_tab(double **tab, int height);
double			**free_failed_alloc(double **tab, int i);

int				handle_mouse_input(int key, int x, int y, t_mlx_win *data);
int				handle_keyboard_input(int key, t_mlx_win *data);
void			init_default_values(t_range *range, t_mlx_win *data);

t_complex		add_complex(t_complex nb1, t_complex nb2);
t_complex		binomial_squares(t_complex nb);

int				palette_shifting(t_range *range, int *colors);

void			palette_one(int *colors);
void			palette_two(int *colors);
void			palette_three(int *colors);
void			palette_four(int *colors);

int				fractal_master_func(t_mlx_win *data, t_data *img,
					t_range *range);

int				create_trgb(int t, int r, int g, int b);
int				mandelbrot(int max_iter, t_complex nb, t_complex c_plot);
int				cardioid_check(t_complex nb);
int				julia(int max_iter, t_complex nb, t_complex c_plot);
int				burning_ship(int max_iter, t_complex px, t_complex c_plot);

int				ft_free_mlx(t_mlx_win *data);
double			ft_atoi_double(const char *nptr);
int				args_parsing(int argc, char **argv, t_range *range);
int				pick_a_fractal(int argc, char *str, t_range *range);

int				print_error(void);

#endif
