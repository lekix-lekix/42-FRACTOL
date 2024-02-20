/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:07:59 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/20 15:26:50 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

double	**get_fractal_px_iter(t_data *img, t_range *range, int max_iter)
{
	int			i;
	int			j;
	int			iter;
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
			iter = mandelbrot(max_iter, px);
			px_iter_tab[i][j] = iter;
		}
	}
	return (px_iter_tab);
}

int fractal_master_func(t_data *img, t_range *range, int max_iter)
{
	double	**px_iter_tab;
	int		*colors;

    (void) max_iter;
	px_iter_tab = get_fractal_px_iter(img, range, max_iter);
	if (!px_iter_tab)
		return (-1); // need to free color_tab // malloc ok
	normalize_data(px_iter_tab, img->height, img->width);
	colors = create_color_segments(range->colors_palette);
	if (!colors)
		return (free(colors), ft_free_tab(px_iter_tab, img->height), -1); // need to free color_tab // malloc ok
	colors = color_shift(colors, range->colors_idx);
	color_gradient_px_put(img, px_iter_tab, colors);
	ft_free_tab(px_iter_tab, img->height);
    free(colors);
    return (0);
}

int	init_fractal_img(t_mlx_win *data, t_range *range)
{
	t_data	*img;

	img = create_image(data);
	if (!img)
		return (ft_free_mlx(data), -1); // malloc ok
	if (fractal_master_func(img, range, range->max_iter) == -1)
    {
       mlx_destroy_image(data->mlx, img->img); //malloc ok
       return (free(img), -1);
    }
	mlx_put_image_to_window(data->mlx, data->window, img->img, 0, 0);
	mlx_destroy_image(data->mlx, img->img);
    free(img);
	return (0);
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
	data.mlx = mlx_init(); // malloc ok 
	if (!data.mlx)
		return (-1);
	data.window = mlx_new_window(data.mlx, data.width, data.height, "fract-ol");
	if (!data.window)
		return (ft_free_mlx(&data), -1);  // malloc ok
	if (init_fractal_img(&data, &range) == -1)
		return (ft_free_mlx(&data), -1); // malloc ok
    mlx_hook(data.window, 17, 1L << 17, ft_free_mlx, &data);
	mlx_hook(data.window, 2, (1L << 0), handle_keyboard_input, &data);
	mlx_hook(data.window, 4, (1L << 2), handle_mouse_input, &data);
	mlx_loop(data.mlx);
	return (0);
}
