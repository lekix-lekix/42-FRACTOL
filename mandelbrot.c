/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:07:02 by kipouliq          #+#    #+#             */
/*   Updated: 2024/01/30 17:16:52 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"
#include <stdio.h>

t_complex	binomial_squares(t_complex nb)
{
	t_complex	result;

    result.real = nb.real * nb.real - nb.img * nb.img;
    result.img = 2 * nb.real * nb.img;
    return (result);
}

t_complex	add_complex(t_complex nb1, t_complex nb2)
{
	t_complex	result;

	result.real = nb1.real + nb2.real;
	result.img = nb1.img + nb2.img;
	return (result);
}

t_complex	mandelbrot_recursive(int i, t_complex nb)
{
	t_complex	result;

	if (i == 0)
	{
		result.real = 0;
		result.img = 0;
		return (result);
	}
	result = add_complex(binomial_squares(mandelbrot_recursive(i - 1, nb)), nb);
	return (result);
}

// int	main(void)
// {
// 	t_complex coordinates;
// 	t_complex result;

// 	coordinates.real = 0;
// 	coordinates.img = 0.5;
// 	result.real = 0;
// 	result.img = 0.5;
//     result = binomial_squares(result);
// 	coordinates = mandelbrot_recursive(4, coordinates);    
//     printf("reel = %f img = %f\n", coordinates.real, coordinates.img);
// }