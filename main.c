#include "./fractol.h"
#include "./minilibx-linux/mlx.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

double	**get_mandel_px_iter(t_data *img, t_range *range, int max_iter)
{
	int			i;
	int			j;
	int			mandel_i;
	double		**px_iter_tab;
	t_complex	px;

	i = -1;
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
	colors = create_color_segments(range->colors_palette);
	if (!colors)
		return ; // need to free color_tab
	colors = color_shift(colors, range->colors_idx);
	color_gradient_px_put(img, px_iter_tab, colors);
	ft_free_tab(px_iter_tab, img->height);
}

void	init_default_values(t_range *range, t_mlx_win *data, int palette)
{
	range->min_x = -3;
	range->max_x = 3;
	range->min_y = -3;
	range->max_y = 3;
	range->max_iter = 25;
	range->c_plot.real = 0;
	range->c_plot.img = 0;
	range->trans_x = 0;
	range->trans_y = 0;
	range->colors_idx = 0;
	range->colors_palette = palette;
	data->width = 1000;
	data->height = 800;
	data->range = range;
}

int	main(int argc, char **argv)
{
	t_range		range;
	t_mlx_win	data;

    (void) argc;
	init_default_values(&range, &data, atoi(argv[1]));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (-1);
	data.window = mlx_new_window(data.mlx, data.width, data.height, "fract-ol");
	if (!data.window)
		return (-1);
	if (init_fractal_img(&data, &range) == -1)
		return (-1); // need free
	mlx_hook(data.window, 2, (1L << 0), handle_keyboard_input, &data);
	mlx_hook(data.window, 4, (1L << 2), handle_mouse_input, &data);
	mlx_loop(data.mlx);
	return (0);
}
