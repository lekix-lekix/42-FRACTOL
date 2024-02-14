#include "./fractol.h"
#include "./minilibx-linux/mlx.h"
#include "math.h"
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>

int	**free_failed_alloc(int **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

int	*ft_free_tab(double **tab, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	my_mlx_px_put(t_data *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	assign_color(float percent)
{
	int	color;

	color = percent * 255;
	return (color);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	min(double **data, int height, int width)
{
	int		i;
	int		j;
	double	min;

	i = -1;
	min = data[0][0];
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (data[i][j] < min)
				min = data[i][j];
		}
	}
	return (min);
}

int	max(double **data, int height, int width)
{
	int		i;
	int		j;
	double	max;

	i = -1;
	max = data[0][0];
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (data[i][j] > max)
				max = data[i][j];
		}
	}
	return (max);
}

t_complex	pixel_to_complex(int x, int y, int width, int height,
		t_range *range)
{
	t_complex	coordinates;
	double		x_percent;
	double		y_percent;

	x_percent = (double)x / (double)width;
	y_percent = (double)y / (double)height;
	coordinates.real = range->min_x + (range->max_x - range->min_x) * x_percent
		- range->trans_x;
	coordinates.img = range->min_y + (range->max_y - range->min_y) * y_percent
		- range->trans_y;
	coordinates.img *= -1;
	return (coordinates);
}

int	**ft_alloc_tab(int width, int height)
{
	register int	i;
	register int	j;
	int				**tab;

	i = 0;
	tab = malloc(sizeof(int *) * (height + 1));
	if (!tab)
		return (NULL);
	while (i < height)
	{
		tab[i] = malloc(sizeof(int) * (width + 1));
		if (!tab[i])
			return (free_failed_alloc(tab, i));
		j = -1;
		while (++j < width)
			tab[i][j] = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

double	**ft_alloc_tab_double(int width, int height)
{
	int		i;
	int		j;
	double	**tab;

	i = 0;
	tab = malloc(sizeof(double *) * height + 1);
	if (!tab)
		return (NULL);
	while (i < height)
	{
		j = -1;
		tab[i] = malloc(sizeof(double) * width + 1);
		while (++j < width)
			tab[i][j] = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	add_colors(int color_a, int color_b)
{
	int	color;

	color = create_trgb(get_t(color_a) + get_t(color_b), get_r(color_a)
			+ get_r(color_b), get_g(color_a) + get_g(color_b), get_b(color_a)
			+ get_b(color_b));
	return (color);
}

int	calc_diff(int a, int b)
{
	if (a > b)
		return (a - b);
	else
		return (b - a);
}

int	diff_colors(int color_a, int color_b)
{
	int	color;
	int	diff_t;
	int	diff_r;
	int	diff_g;
	int	diff_b;

	diff_t = calc_diff(get_t(color_a), get_t(color_b));
	diff_r = calc_diff(get_r(color_a), get_r(color_b));
	diff_g = calc_diff(get_g(color_a), get_g(color_b));
	diff_b = calc_diff(get_b(color_a), get_b(color_b));
	color = create_trgb(diff_t, diff_r, diff_g, diff_b);
	return (color);
}

int	color_multiply(int color, float mult)
{
	int	final_color;

	final_color = create_trgb(get_t(color) * mult, get_r(color) * mult,
			get_g(color) * mult, get_b(color) * mult);
	return (final_color);
}

int	*color_interpolation(int color_a, int color_b, int max_iter)
{
	int		i;
	int		diff;
	float	mult;
	int		*color_tab;

	i = 0;
	color_tab = malloc(sizeof(int) * max_iter);
	if (!color_tab)
		return (NULL);
	diff = diff_colors(color_a, color_b);
	max_iter -= 1;
	while (i <= max_iter)
	{
		mult = (float)i / (float)max_iter;
		color_tab[i] = add_colors(color_a, color_multiply(diff, mult));
		i++;
	}
	return (color_tab); // pas sur que ca marche bien
}

// void	color_gradient_px_put(t_data *img, double **px_iter_tab, int max_iter)
// {
// 	register int	i;
// 	register int	j;
// 	int				color;
// 	int				*color_tab;

// 	color_tab = color_interpolation(img->color_a, img->color_b, max_iter);
//     i = 0;
//     while (i < max_iter)
//     {
//         printf("color tab %d = %d,%d,%d,%d\n", i, get_t(color_tab[i]),
// get_r(color_tab[i]), get_g(color_tab[i]), get_b(color_tab[i]));
//         i++;
//     }
// 	if (!color_tab)
// 		return ; // will need to return something else
// 	i = -1;
// 	while (++i < img->height)
// 	{
// 		j = -1;
// 		while (++j < img->width)
// 		{
// 			color = color_tab[px_iter_tab[i][j]];
// 			my_mlx_px_put(img, j, i, color);
// color = px_iter_tab[i][j] * 255 / (max_iter / 3);
// if (px_iter_tab[i][j] == max_iter)
// 	continue ;
// else if (px_iter_tab[i][j] < max_iter / 5)
// 	my_mlx_px_put(img, j, i, create_trgb(0, color, 0, 0));
// else if (px_iter_tab[i][j] >= max_iter / 5
// 	&& px_iter_tab[i][j] <= (max_iter / 5) * 2)
// 	my_mlx_px_put(img, j, i, create_trgb(0, 255, color, 0));
// else
// 	my_mlx_px_put(img, j, i, create_trgb(0, 255, 255, color));
// 		}
// 	}
// 	free(color_tab);
// }

double	normalize_value(double value, double min, double max)
{
	return ((value - min) / (max - min));
}

void	normalize_data(double **data, int height, int width)
{
	double	min_val;
	double	max_val;
	int		i;
	int		j;

	min_val = min(data, height, width);
	max_val = max(data, height, width);
	// printf("min = %f, max = %f\n", min_val, max_val);
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			data[i][j] = normalize_value(data[i][j], min_val, max_val);
	}
}

int	interpolate_color(int color_a, int color_b, double t)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color_a) * (1 - t) + get_r(color_b) * t;
	g = get_g(color_a) * (1 - t) + get_g(color_b) * t;
	b = get_b(color_a) * (1 - t) + get_b(color_b) * t;
	// printf("r g b %d %d %d\n", r, g, b);
	return (create_trgb(0, r, g, b));
}

void	color_gradient_px_put(t_data *img, double **px_iter_tab, int *colors)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			if (px_iter_tab[i][j] == 1)
				color = create_trgb(0, 0, 0, 0);
			else if (px_iter_tab[i][j] >= 0 && px_iter_tab[i][j] <= 0.16)
				color = interpolate_color(colors[0], colors[1],
						normalize_value(px_iter_tab[i][j], 0, 0.16));
			else if (px_iter_tab[i][j] > 0.16 && px_iter_tab[i][j] <= 0.42)
				color = interpolate_color(colors[1], colors[2],
						normalize_value(px_iter_tab[i][j], 0.16, 0.42));
			else if (px_iter_tab[i][j] > 0.42 && px_iter_tab[i][j] <= 0.6425)
				color = interpolate_color(colors[2], colors[3],
						normalize_value(px_iter_tab[i][j], 0.42, 0.6425));
			else if (px_iter_tab[i][j] > 0.6425 && px_iter_tab[i][j] <= 0.8575)
				color = interpolate_color(colors[3], colors[4],
						normalize_value(px_iter_tab[i][j], 0.6425, 0.8575));
			else
				color = interpolate_color(colors[3], colors[4],
						normalize_value(px_iter_tab[i][j], 0.8573, 1));
			my_mlx_px_put(img, j, i, color);
		}
	}
}

int *pick_color(int *colors_segments, int index)
{
    int i;
    int j;
    int *colors;

    colors = malloc(sizeof(int) * 5);
    if (!colors)
        return (NULL);
    i = 0;
    j = index;
    while (i < 5)
    {
        if (j == 5)
            j = 0;
        colors[i] = colors_segments[j];
        i++;
        j++;
    }
    return (colors);
}
int	*create_color_segments(void)
{
	int	*color_segments;

	color_segments = malloc(sizeof(int) * 5);
	if (!color_segments)
		return (NULL);
	color_segments[0] = create_trgb(0, 255, 0, 0);
	color_segments[1] = create_trgb(0, 255, 255, 0);
	color_segments[2] = create_trgb(0, 0, 255, 0);
	color_segments[3] = create_trgb(0, 0, 255, 255);
	color_segments[4] = create_trgb(0, 0, 0, 255);
	return (color_segments);
}

double	**get_mandel_px_iter(t_data *img, t_range *range, int max_iter)
{
	int			i;
	int			j;
	int			mandel_i;
	double		**px_iter_tab;
	t_complex	px;

	i = -1;
	printf("width %d height %d\n", img->width, img->height);
	px_iter_tab = ft_alloc_tab_double(img->width, img->height);
	if (!px_iter_tab)
		return (NULL);
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			px = pixel_to_complex(j, i, img->width, img->height, range);
			mandel_i = mandelbrot(max_iter, px);
			px_iter_tab[i][j] = mandel_i;
		}
	}
	return (px_iter_tab);
}

void	fractal_master_func(t_data *img, t_range *range, int max_iter)
{
	double	**px_iter_tab;
	int		*colors;

	px_iter_tab = get_mandel_px_iter(img, range, max_iter);
	if (!px_iter_tab)
		return ; // need to free color_tab
	normalize_data(px_iter_tab, img->height, img->width);
	colors = create_color_segments();
	if (!colors)
		return ; // need to free color_tab
	color_gradient_px_put(img, px_iter_tab, colors);
	ft_free_tab(px_iter_tab, img->height);
	// free(color_tab);
}

t_data	*create_image(t_mlx_win *data)
{
	t_data	*img;

	img = malloc(sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!(img->img))
		return (NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->width = data->width;
	img->height = data->height;
	return (img);
}

int	init_fractal_img(t_mlx_win *data, t_range *range)
{
	t_data	*img;

	img = create_image(data);
	if (!img)
		return (-1);
	fractal_master_func(img, range, range->max_iter);
	mlx_put_image_to_window(data->mlx, data->window, img->img, 0, 0);
	mlx_destroy_image(data->mlx, img->img);
	return (0);
}

void	zoom_in(t_mlx_win *data)
{
	data->range->min_x *= 0.5;
	data->range->max_x *= 0.5;
	data->range->min_y *= 0.5;
	data->range->max_y *= 0.5;
}

void	translate_zoom_in(t_mlx_win *data)
{
	int			mouse_x;
	int			mouse_y;
	t_complex	mouse_pos;

	mlx_mouse_get_pos(data->mlx, data->window, &mouse_x, &mouse_y);
	mouse_pos = pixel_to_complex(mouse_x, mouse_y, data->width, data->height,
			data->range);
	data->range->trans_x -= fabs(data->range->trans_x) - fabs(mouse_pos.real);
	data->range->trans_y -= fabs(data->range->trans_y) - fabs(mouse_pos.img);
	zoom_in(data);
	init_fractal_img(data, data->range);
}

void	zoom_out(t_mlx_win *data)
{
	data->range->min_x *= 2;
	data->range->max_x *= 2;
	data->range->min_y *= 2;
	data->range->max_y *= 2;
	init_fractal_img(data, data->range);
}

int	handle_mouse_input(int key, int x, int y, t_mlx_win *data)
{
	int			mouse_x;
	int			mouse_y;
	t_complex	mouse_pos;

	(void)x;
	(void)y;
	mouse_x = 0;
	mouse_y = 0;
	if (key == WHEELUP)
		translate_zoom_in(data);
	if (key == WHEELDOWN)
		zoom_out(data);
	mlx_mouse_get_pos(data->mlx, data->window, &mouse_x, &mouse_y);
	mouse_pos = pixel_to_complex(mouse_x, mouse_y, data->width, data->height,
			data->range);
	return (0);
}

int	handle_keyboard_input(int key, t_mlx_win *data)
{
	printf("key %d\n", key);
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		exit(0);
	}
	if (key == UP_ARROW)
		data->range->trans_y += 0.5;
	if (key == DOWN_ARROW)
		data->range->trans_y -= 0.5;
	if (key == LEFT_ARROW)
		data->range->trans_x += 0.5;
	if (key == RIGHT_ARROW)
		data->range->trans_x -= 0.5;
	if (key == 61)
		data->range->max_iter += 50;
	if (key == 45)
		data->range->max_iter -= 35;
	if (key == 105)
		data->range->c_plot.img += 0.1;
	if (key == 111)
		data->range->c_plot.img -= 0.1;
	if (key == 101)
		data->range->c_plot.real += 0.1;
	if (key == 114)
		data->range->c_plot.real -= 0.1;
	if (key == 48)
		data->range->max_iter = 200;
	init_fractal_img(data, data->range);
	return (0);
}
int	main(void)
{
	t_range		range;
	t_mlx_win	data;

	range.min_x = -2;
	range.max_x = 2;
	range.min_y = -2;
	range.max_y = 2;
	range.max_iter = 200;
	range.c_plot.real = 0;
	range.c_plot.img = 0;
    range.trans_x = -0.5;
	data.width = 1000;
	data.height = 800;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (-1);
	data.window = mlx_new_window(data.mlx, data.width, data.height, "fract-ol");
	if (!data.window)
		return (-1);
	data.range = &range;
	data.range->trans_x = 0;
	data.range->trans_y = 0;
	if (init_fractal_img(&data, &range) == -1)
		return (-1); // need free
	// mlx_key_hook(data.window, handle_input, &data);
	mlx_hook(data.window, 2, (1L << 0), handle_keyboard_input, &data);
	mlx_hook(data.window, 4, (1L << 2), handle_mouse_input, &data);
	mlx_loop(data.mlx);
	return (0);
}

// cc -Wall -Wextra -Werror -I ./minilibx-linux main.c mandelbrot.c
	// -L ./minilibx-linux/ -lmlx -lXext -lX11 -lm -g3 -O3