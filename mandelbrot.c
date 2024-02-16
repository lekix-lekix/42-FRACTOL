/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:07:02 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/16 12:15:18 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"
#include <math.h>
#include <stdio.h>

double  square(double nb)
{
    return (nb * nb);
}

t_complex	binomial_squares(t_complex nb)
{ 
    t_complex   result;
    
	result.real = nb.real * nb.real - nb.img * nb.img;
	result.img = 2 * nb.real * nb.img;
	return (result);
}

t_complex	add_complex(t_complex nb1, t_complex nb2)
{
    t_complex   result;
        
	result.real = nb1.real + nb2.real;
	result.img = nb1.img + nb2.img;
	return (result);
}

t_complex	calc_mandelbrot(t_complex mandel, t_complex nb)
{
    t_complex result;

    result = add_complex(binomial_squares(mandel), nb);
    return (result);
}

int cardioid_check(t_complex nb)
{
    double q;
    double result;

    q = square(nb.real - 0.25) + square(nb.img);
    result = q *(q + (nb.real - 0.25));
    if (result <= 0.25 * square(nb.img) || square(nb.real + 1) + square(nb.img) <= 0.0625)
        return (1);
    return (0);
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
