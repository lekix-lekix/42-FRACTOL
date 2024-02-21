/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_display_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:07:18 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/21 18:10:01 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

void	my_mlx_px_put(t_data *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

t_data	*create_image(t_mlx_win *data)
{
	t_data	*img;

	img = malloc(sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!(img->img))
		return (free(img), NULL);
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
		return (ft_free_mlx(data), -1); // malloc ok
	if (fractal_master_func(img, range) == -1)
	{
		mlx_destroy_image(data->mlx, img->img); // malloc ok
		return (free(img), -1);
	}
	mlx_put_image_to_window(data->mlx, data->window, img->img, 0, 0);
	mlx_destroy_image(data->mlx, img->img);
	free(img);
	return (0);
}