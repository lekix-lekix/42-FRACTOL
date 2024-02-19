/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:04:34 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/19 18:43:38 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

void	handle_arrow_inputs(int key, t_mlx_win *data)
{
	if (key == UP_ARROW)
		data->range->trans_y += 0.5;
	if (key == DOWN_ARROW)
		data->range->trans_y -= 0.5;
	if (key == LEFT_ARROW)
		data->range->trans_x += 0.5;
	if (key == RIGHT_ARROW)
		data->range->trans_x -= 0.5;
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
	if (key == C)
	{
		if (data->range->colors_idx == 4)
			data->range->colors_idx = 0;
		else
			data->range->colors_idx++;
	}
}

int	handle_keyboard_input(int key, t_mlx_win *data)
{
	if (key == ESCAPE)
	{
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		exit(0);
	}
	else if (key == UP_ARROW || key == DOWN_ARROW || key == LEFT_ARROW
		|| key == RIGHT_ARROW)
		handle_arrow_inputs(key, data);
	else if (key == R)
		init_default_values(data->range, data, data->range->colors_palette);
	else
		handle_key_inputs(key, data);
	init_fractal_img(data, data->range);
	return (0);
}
