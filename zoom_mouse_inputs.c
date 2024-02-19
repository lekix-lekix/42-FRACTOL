/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_mouse_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:22:09 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/19 17:24:21 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

void	zoom_out(t_mlx_win *data)
{
	data->range->min_x *= 2;
	data->range->max_x *= 2;
	data->range->min_y *= 2;
	data->range->max_y *= 2;
}

void	zoom_in(t_mlx_win *data)
{
	data->range->min_x *= 0.5;
	data->range->max_x *= 0.5;
	data->range->min_y *= 0.5;
	data->range->max_y *= 0.5;
}

void	translate_zoom_in(t_mlx_win *data)
{
	int			mouse_x;
	int			mouse_y;
	t_complex	mouse_pos;

	mlx_mouse_get_pos(data->mlx, data->window, &mouse_x, &mouse_y);
	mouse_pos = pixel_to_complex(mouse_x, mouse_y, data->width, data->height,
			data->range);
	data->range->trans_x = mouse_pos.real * -1;
	data->range->trans_y = mouse_pos.img * -1;
	zoom_in(data);
}

int	handle_mouse_input(int key, int x, int y, t_mlx_win *data)
{
	(void)x;
	(void)y;
	if (key == WHEELUP)
		translate_zoom_in(data);
	if (key == WHEELDOWN)
		zoom_out(data);
	init_fractal_img(data, data->range);
	return (0);
}
