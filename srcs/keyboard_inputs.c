/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:04:34 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/22 15:44:17 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	handle_arrow_inputs(int key, t_mlx_win *data)
{
	double	shift_vert;
	double	shift_hztal;

	shift_vert = (data->range->max_x + fabs(data->range->min_x)) * 0.05;
	shift_hztal = (data->range->max_y + fabs(data->range->min_y)) * 0.05;
	if (key == UP_ARROW)
		data->range->trans_y += shift_vert;
	if (key == DOWN_ARROW)
		data->range->trans_y -= shift_vert;
	if (key == LEFT_ARROW)
		data->range->trans_x += shift_hztal;
	if (key == RIGHT_ARROW)
		data->range->trans_x -= shift_hztal;
}

void	handle_key_inputs(int key, t_mlx_win *data)
{
	if (key == PLUS)
		data->range->max_iter += 50;
	if (key == MINUS)
		data->range->max_iter -= 35;
	if (key == I && data->range->c_plot.img < 4)
		data->range->c_plot.img += 0.01;
	if (key == O && data->range->c_plot.img > -4)
		data->range->c_plot.img -= 0.01;
	if (key == Y && data->range->c_plot.real < 4)
		data->range->c_plot.real += 0.01;
	if (key == U && data->range->c_plot.real > -4)
		data->range->c_plot.real -= 0.01;
	if (key == KEY_0)
		data->range->max_iter = 25;
}

void	handle_color_inputs(int key, t_range *range)
{
	if (key == C)
	{
		if (range->colors_idx == 4)
			range->colors_idx = 0;
		else
			range->colors_idx++;
	}
	if (key == P)
	{
		if (range->colors_palette == 3)
			range->colors_palette = 0;
		else
			range->colors_palette++;
	}
}

int	handle_keyboard_input(int key, t_mlx_win *data)
{
	if (key == ESCAPE)
		ft_free_mlx(data);
	else if (key == UP_ARROW || key == DOWN_ARROW || key == LEFT_ARROW
		|| key == RIGHT_ARROW)
		handle_arrow_inputs(key, data);
	else if (key == R)
		init_default_values(data->range, data);
	else if (key == C || key == P)
		handle_color_inputs(key, data->range);
	else
		handle_key_inputs(key, data);
	init_fractal_img(data, data->range);
	return (0);
}
