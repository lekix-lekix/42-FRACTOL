/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:08:54 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/20 10:56:36 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

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
