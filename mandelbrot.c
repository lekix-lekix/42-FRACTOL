/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:07:02 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/13 13:50:56 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"
#include <math.h>
#include <stdio.h>

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


// int has_escaped(t_complex nb)
// {
//     return (nb.real < -2 || nb.real > 2 || nb.img < -2 || nb.img > 2);
// }

int	mandelbrot(int max_iter, t_complex nb)
{
	int			i;
	t_complex	result;

    i = 0;
    result.real = 0;
    result.img = 0;
    while (i < max_iter && fabs(result.real) < 5000 && fabs(result.img) < 5000)
    {
        result = calc_mandelbrot(result, nb);
        // printf("res = %f | %f\n", result.real, result.img);
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
    while (i < max_iter && fabs(result.real) < 2 && fabs(result.img) < 2)
    {
        result = calc_julia(result, c_plot);
        i++;
    }
    return (i);
}
