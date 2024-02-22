/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:07:59 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/22 15:44:19 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

double	**get_fractal_px_iter(t_mlx_win *data, t_range *range, t_fractal_func f)
{
	int			i;
	int			j;
	int			iter;
	double		**px_iter_tab;
	t_complex	px;

	i = -1;
	px_iter_tab = ft_alloc_tab_double(data->width, data->height);
	if (!px_iter_tab)
		return (NULL);
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			px = pixel_to_complex(j, i, data, range);
			iter = f(range->max_iter, px, range->c_plot);
			px_iter_tab[i][j] = iter;
		}
	}
	return (px_iter_tab);
}

t_fractal_func	return_fractal_func(t_range *range)
{
	if (range->fractal == 0)
		return (mandelbrot);
	else if (range->fractal == 1)
		return (julia);
	else
		return (burning_ship);
}

int	fractal_master_func(t_mlx_win *data, t_data *img, t_range *range)
{
	double	**px_iter_tab;
	int		*colors;

	px_iter_tab = get_fractal_px_iter(data, range, return_fractal_func(range));
	if (!px_iter_tab)
		return (-1);
	normalize_data(px_iter_tab, data->height, data->width);
	colors = create_color_segments(range->colors_palette);
	if (!colors)
		return (free(colors), ft_free_tab(px_iter_tab, data->height), -1);
	colors = color_shift(colors, range->colors_idx);
	color_gradient_px_put(img, px_iter_tab, colors);
	ft_free_tab(px_iter_tab, data->height);
	free(colors);
	return (0);
}

void	init_default_values(t_range *range, t_mlx_win *data)
{
	range->min_x = -3;
	range->max_x = 3;
	range->min_y = -3;
	range->max_y = 3;
	range->max_iter = 25;
	range->trans_x = 0;
	range->trans_y = 0;
	range->colors_idx = 0;
	range->colors_palette = 1;
	data->width = 1000;
	data->height = 800;
	data->range = range;
}

int	main(int argc, char **argv)
{
	t_range		range;
	t_mlx_win	data;

	if (!args_parsing(argc, argv, &range))
		return (print_error());
	init_default_values(&range, &data);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (-1);
	data.window = mlx_new_window(data.mlx, data.width, data.height, "fract-ol");
	if (!data.window)
		return (ft_free_mlx(&data), -1);
	if (init_fractal_img(&data, &range) == -1)
		return (ft_free_mlx(&data), -1);
	mlx_hook(data.window, 17, 1L << 17, ft_free_mlx, &data);
	mlx_hook(data.window, 2, (1L << 0), handle_keyboard_input, &data);
	mlx_hook(data.window, 4, (1L << 2), handle_mouse_input, &data);
	mlx_loop(data.mlx);
	return (0);
}
