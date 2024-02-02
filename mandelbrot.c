/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:07:02 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/02 13:32:24 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"
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

int has_escaped(t_complex nb)
{
    return (nb.real < -2 || nb.real > 2 || nb.img < -2 || nb.img > 2);
}

int	mandelbrot(int max_iter, t_complex nb)
{
	int			i;
	t_complex	result;

    i = 0;
    result.real = 0;
    result.img = 0;
    while (i < max_iter && !has_escaped(result))
    {
        result = calc_mandelbrot(result, nb);
        // printf("res = %f | %f\n", result.real, result.img);
        i++;
    }
	return (i);
}

// int	main(void)
// {
// 	t_complex nb;

// 	nb.real = 0;
// 	nb.img = 0.2;
// 	int i = mandelbrot(20, nb);
// 	printf("i = %d\n", i);
// }