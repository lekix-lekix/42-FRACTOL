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

int	*ft_free_tab(int **tab, int height)
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

	// printf("px ")
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	assign_color(float percent)
{
	int	color;

	color = percent * 255;
	// printf("color = %d\n", color);
	return (color);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_complex	pixel_to_complex(int x, int y, int width, int height,
		t_range *range)
{
	t_complex	coordinates;
	double		x_percent;
	double		y_percent;

	x_percent = (double)x / (double)width;
	y_percent = (double)y / (double)height;
	// printf("rmin x %g crmax x %f rmin y %f rmax y %f\n", range->min_x,
		// range->max_x, range->min_y, range->max_y);
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
		// printf("i = %d\n", i);
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

float	**ft_alloc_tab_float(int width, int height)
{
	register int	i;
	register int	j;
	float			**tab;

	i = 0;
	tab = malloc(sizeof(float *) * height + 1);
	if (!tab)
		return (NULL);
	while (i < height)
	{
		j = -1;
		tab[i] = malloc(sizeof(float) * width + 1);
		while (++j < width)
			tab[i][j] = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	color_gradient_px_put(t_data *img, int **px_iter_tab, int max_iter)
{
	register int	i;
	register int	j;
	int				color;

	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			color = px_iter_tab[i][j] * 255 / (max_iter / 3);
			if (px_iter_tab[i][j] == max_iter)
				continue ;
			else if (px_iter_tab[i][j] < max_iter / 5)
				my_mlx_px_put(img, j, i, create_trgb(0, color, 0, 0));
			else if (px_iter_tab[i][j] >= max_iter / 5
				&& px_iter_tab[i][j] <= (max_iter / 5) * 2)
				my_mlx_px_put(img, j, i, create_trgb(0, 255, color, 0));
			else
				my_mlx_px_put(img, j, i, create_trgb(0, 255, 255, color));
		}
	}
}

int	**get_mandel_px_iter(t_data *img, t_range *range, int *color_tab,
		int max_iter)
{
	register int	i;
	register int	j;
	int				mandel_i;
	int				**px_iter_tab;
	t_complex		px;

	i = -1;
	printf("width %d height %d\n", img->width, img->height);
	px_iter_tab = ft_alloc_tab(img->width, img->height);
	if (!px_iter_tab)
		return (NULL);
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			px = pixel_to_complex(j, i, img->width, img->height, range);
			mandel_i = mandelbrot(max_iter, px);
			color_tab[mandel_i - 1]++;
			px_iter_tab[i][j] = mandel_i;
		}
	}
	printf("coucou\n");
	return (px_iter_tab);
}

void	fractal_master_func(t_data *img, t_range *range, int max_iter)
{
	int	**px_iter_tab;
	int	*color_tab;

	color_tab = malloc(sizeof(int) * max_iter);
	if (!color_tab)
		return ;
	px_iter_tab = get_mandel_px_iter(img, range, color_tab, max_iter);
	if (!px_iter_tab)
		return ; // need to free color_tab
	color_gradient_px_put(img, px_iter_tab, max_iter);
	ft_free_tab(px_iter_tab, img->height);
	free(color_tab);
}

t_data	*create_image(void *mlx, int width, int height)
{
	t_data	*img;

	img = malloc(sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, width, height);
	if (!(img->img))
		return (NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->width = width;
	img->height = height;
	return (img);
}

int	init_fractal_img(t_mlx_win *data, t_range *range)
{
	t_data	*img;

	img = create_image(data->mlx, data->width, data->height);
	if (!img)
		return (-1);
	fractal_master_func(img, range, 100);
	mlx_put_image_to_window(data->mlx, data->window, img->img, 0, 0);
	mlx_destroy_image(data->mlx, img->img);
	return (0);
}

int	handle_input(int keysym, t_mlx_win *data)
{
	int			mouse_x;
	int			mouse_y;
	t_complex	mouse_pos;

	mouse_x = 0;
	mouse_y = 0;
	printf("keypress = %d\n", keysym);
	// printf("mlx %p window %p\n", data->mlx, data->window);
	if (keysym == XK_Escape)
	{
		printf("%p mlx %p window\n", data->mlx, data->window);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		exit(0);
	}
	if (keysym == 65513)
	{
		data->range->min_x *= 0.5;
		data->range->max_x *= 0.5;
		data->range->min_y *= 0.5;
		data->range->max_y *= 0.5;
		init_fractal_img(data, data->range);
	}
	if (keysym == 65535)
	{
		data->range->min_x /= 10;
		data->range->max_x /= 10;
		data->range->min_y /= 10;
		data->range->max_y /= 10;
		init_fractal_img(data, data->range);
	}
	if (keysym == 65362)
	{
		data->range->trans_y -= 0.1;
		init_fractal_img(data, data->range);
	}
	if (keysym == 65364)
	{
		data->range->trans_y += 0.1;
		init_fractal_img(data, data->range);
	}
	if (keysym == 65361)
	{
		data->range->trans_x += 0.1;
		init_fractal_img(data, data->range);
	}
	if (keysym == 65363)
	{
		data->range->trans_x -= 0.1;
		init_fractal_img(data, data->range);
	}
	mlx_mouse_get_pos(data->mlx, data->window, &mouse_x, &mouse_y);
	printf("mousex %d mousey %d\n", mouse_x, mouse_y);
	mouse_pos = pixel_to_complex(mouse_x, mouse_y, data->width, data->height,
			data->range);
	printf("mouse reel %f, mouse img %f\n", mouse_pos.real, mouse_pos.img);
	// free(data->mlx);
	// free(data->window);c
	return (0);
}

int	main(void)
{
	t_mlx_win	data;
	t_range		range;

	range.min_x = -2;
	range.min_y = -2;
	range.max_x = 2;
	range.max_y = 2;
	data.width = 1200;
	data.height = 1000;
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
	mlx_hook(data.window, 2, (1L << 0), handle_input, &data);
	mlx_loop(data.mlx);
	return (0);
}
