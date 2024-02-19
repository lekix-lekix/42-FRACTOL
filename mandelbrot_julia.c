/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:07:02 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/19 18:11:17 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

t_complex	calc_mandelbrot(t_complex mandel, t_complex nb)
{
    t_complex result;

    result = add_complex(binomial_squares(mandel), nb);
    return (result);
}

int	mandelbrot(int max_iter, t_complex nb)
{
	int			i;
	t_complex	result;

    i = 0;
    result.real = 0;    
    result.img = 0;
    while (i < max_iter)
    {
        if (result.real * result.real + result.img * result.img > 9)
            return (i);
        if (cardioid_check(nb))
            return (max_iter);
        result = calc_mandelbrot(result, nb);
        i++;
    }
	return (i);
}

t_complex calc_julia(t_complex result, t_complex c_plot)
{
    result = add_complex(binomial_squares(result), c_plot);
    return (result);
}

int julia(int max_iter, t_complex px, t_complex c_plot)
{
    int i;
    t_complex   result;

    i = 0;
    result.real = px.real;
    result.img = px.img;
    while (i < max_iter /* && fabs(result.real) < 2 && fabs(result.img) < 2 */)
    {
        if (result.real * result.real + result.img * result.img > 3 * 3)
            return (i);
        result = calc_julia(result, c_plot);
        i++;
    }
    return (i);
}
