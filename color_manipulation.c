/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:24:27 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/22 15:05:39 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

int	interpolate_color(int color_a, int color_b, double t)
{
	int	r;
	int	g;
	int	b;

	r = get_r(color_a) * (1 - t) + get_r(color_b) * t;
	g = get_g(color_a) * (1 - t) + get_g(color_b) * t;
	b = get_b(color_a) * (1 - t) + get_b(color_b) * t;
	return (create_trgb(0, r, g, b));
}

int	get_color_gradient(double iter, int *colors)
{
	if (iter >= 0 && iter <= 0.16)
		return (interpolate_color(colors[0], colors[1], normalize_value(iter, 0,
					0.16)));
	else if (iter > 0.16 && iter <= 0.42)
		return (interpolate_color(colors[1], colors[2], normalize_value(iter,
					0.16, 0.42)));
	else if (iter > 0.42 && iter <= 0.6425)
		return (interpolate_color(colors[2], colors[3], normalize_value(iter,
					0.42, 0.6425)));
	else if (iter > 0.6425 && iter <= 0.8575)
		return (interpolate_color(colors[3], colors[4], normalize_value(iter,
					0.6425, 0.8575)));
	else
		return (interpolate_color(colors[3], colors[4], normalize_value(iter,
					0.8573, 1)));
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
				continue ;
			else
				color = get_color_gradient(px_iter_tab[i][j], colors);
			my_mlx_px_put(img, j, i, color);
		}
	}
}

int	*color_shift(int *colors_segments, int index)
{
	int	i;
	int	j;
	int	*colors;

	if (!index)
		return (colors_segments);
	colors = malloc(sizeof(int) * 5);
	if (!colors)
		return (NULL);
	i = 0;
	j = index;
	while (i < 5)
	{
		if (j == 4)
			j = 0;
		colors[i] = colors_segments[j];
		i++;
		j++;
	}
	free(colors_segments);
	return (colors);
}

int	*create_color_segments(int palette_nb)
{
	int	*colors;

	colors = malloc(sizeof(int) * 5);
	if (!colors)
		return (NULL);
	if (palette_nb == 0)
		palette_one(colors);
	else if (palette_nb == 1)
		palette_two(colors);
	else if (palette_nb == 2)
		palette_three(colors);
	else if (palette_nb == 3)
		palette_four(colors);
	return (colors);
}
