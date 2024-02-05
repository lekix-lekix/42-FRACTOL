#include "./fractol.h"
#include "./minilibx-linux/mlx.h"
#include "math.h"
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

t_complex	pixel_to_complex(int x, int y, int height, int width)
{
	t_complex	coordinates;
	float		x_percent;
	float		y_percent;

	x_percent = (float)x / (float)width;
	y_percent = (float)y / (float)height;
	coordinates.real = -3 + (3 - (-3)) * x_percent;
	coordinates.img = -3 + (3 - (-3)) * y_percent;
	return (coordinates);
}

int	**ft_alloc_tab(int width, int height)
{
	int	i;
	int	j;
	int	**tab;

	i = 0;
	tab = malloc(sizeof(int *) * height);
	if (!tab)
		return (NULL);
	while (i < width)
	{
		tab[i] = malloc(sizeof(int) * width);
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
	int		i;
	int		j;
	float	**tab;

	i = 0;
	tab = malloc(sizeof(float *) * height);
	if (!tab)
		return (NULL);
	while (i < width)
	{
		j = -1;
		tab[i] = malloc(sizeof(float) * width);
		while (++j < width)
			tab[i][j] = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	color_gradient_px_put(t_data *img, int **px_iter_tab, int max_iter)
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
			color = px_iter_tab[i][j] * 255 / (max_iter / 5);
			if (px_iter_tab[i][j] == max_iter)
				my_mlx_px_put(img, i, j, create_trgb(0, 1, 186, 239));
			else if (px_iter_tab[i][j] < max_iter / 5)
				my_mlx_px_put(img, i, j, create_trgb(0, color, 0, 0));
			else if (px_iter_tab[i][j] >= max_iter / 5
				&& px_iter_tab[i][j] <= (max_iter / 5) * 2)
				my_mlx_px_put(img, i, j, create_trgb(0, 255, color, 0));
			else
				my_mlx_px_put(img, i, j, create_trgb(0, 255, 255, color));
		}
	}
}

int	**get_mandel_px_iter(t_data *img, int *color_tab, int max_iter)
{
	int			i;
	int			j;
	int			mandel_i;
	int			**px_iter_tab;
	t_complex	px;

	i = -1;
	px_iter_tab = ft_alloc_tab(img->width, img->height);
	if (!px_iter_tab)
		return (NULL);
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			px = pixel_to_complex(i, j, img->height, img->width);
			mandel_i = mandelbrot(max_iter, px);
			color_tab[mandel_i - 1]++;
			px_iter_tab[i][j] = mandel_i;
		}
	}
	return (px_iter_tab);
}

void	fractal_master_func(t_data *img, int max_iter)
{
	int	**px_iter_tab;
	int	*color_tab;

	color_tab = malloc(sizeof(int) * max_iter);
	if (!color_tab)
		return ;
	px_iter_tab = get_mandel_px_iter(img, color_tab, max_iter);
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

int	main()
{
	void	*mlx;
	void	*window;
	t_data	*img;
    t_colors colors;

    mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, 1200, 1200, "wesh la zone");
	if (!window)
		return (-1);
	img = NULL;
	img = create_image(mlx, 1200, 1200);
	if (!img)
		return (-1);
	fractal_master_func(img, 50);
	mlx_put_image_to_window(mlx, window, img->img, 0, 0);
	free(img);
	// mlx_destroy_window(mlx, windeow);
	mlx_loop(mlx);
}
