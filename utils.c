/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:27:58 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/22 15:19:43 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

double	atoi_conversion(const char *nptr)
{
	int		i;
	int		comma;
	double	nb;

	i = -1;
	comma = 0;
	nb = 0;
	while ((nptr[++i] >= '0' && nptr[i] <= '9') || nptr[i] == '.')
	{
		if (nptr[i] == '.')
		{
			comma = i;
			continue ;
		}
		nb = nb * 10 + (nptr[i] - '0');
	}
	if (comma)
	{
		comma += 1;
		nb /= pow(10, i - comma);
		comma--;
	}
	return (nb);
}

double	ft_atoi_double(const char *nptr)
{
	int		i;
	int		neg;
	double	nb;

	nb = 0;
	i = 0;
	neg = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	nb = atoi_conversion(nptr + i);
	if (neg)
		nb = -nb;
	return (nb);
}

int	print_error(void)
{
	ft_printf("It appears that some value is incorrect !\n");
	ft_printf("\n");
	ft_printf("How to use me :\n");
	ft_printf("- Pick a fractal : 'mandelbrot', 'julia' or 'burning_ship'\n");
	ft_printf("- Launch the program : './fractol fractal_name'\n");
	ft_printf("\n");
	ft_printf("For the Julia set,");
	ft_printf("you need to input two starting values");
	ft_printf("next to the fractal name.\n");
	ft_printf("- './fractol julia val1 val2'\n");
	ft_printf("\n");
	ft_printf("These values are floats with up to 6 digits after the comma,");
	ft_printf("but can not be < or > 4.\n");
	ft_printf("Enjoy!\n");
	return (-1);
}
