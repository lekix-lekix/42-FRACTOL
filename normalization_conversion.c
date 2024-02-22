/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization_conversion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:00:00 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/22 15:17:16 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

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

t_complex	pixel_to_complex(int x, int y, t_mlx_win *data, t_range *range)
{
	t_complex	coordinates;
	double		x_percent;
	double		y_percent;

	x_percent = (double)x / data->width;
	y_percent = (double)y / data->height;
	coordinates.real = range->min_x + (range->max_x - range->min_x) * x_percent
		- range->trans_x;
	coordinates.img = range->min_y + (range->max_y - range->min_y) * y_percent
		- range->trans_y;
	return (coordinates);
}

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
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			data[i][j] = normalize_value(data[i][j], min_val, max_val);
	}
}
