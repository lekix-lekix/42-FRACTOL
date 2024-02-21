/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:07:41 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/21 18:11:10 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

int	check_julia_values(char *str)
{
	int	i;
	int	comma;

	i = -1;
	comma = 0;
	while (str[++i])
	{
		if (str[0] == '+' || str[0] == '-')
			continue ;
		if (!is_num(str[i]))
			return (0);
		if (str[i] == '.')
			comma++;
	}
	if (comma > 1)
		return (0);
	return (1);
}

int	args_parsing(int argc, char **argv, t_range *range)
{
	if (argc == 1 || !pick_a_fractal(argc, argv[1], range))
		return (-1);
	if (range->fractal == 1)
	{
		if (!check_julia_values(argv[2]) || !check_julia_values(argv[3]))
			return (-1);
		if (ft_strlen(argv[2]) > 9 || ft_strlen(argv[3]) > 9)
			return (-1);
		range->c_plot.real = ft_atoi_double(argv[2]);
		range->c_plot.img = ft_atoi_double(argv[3]);
	}
	return (0);
}

int	pick_a_fractal(int argc, char *str, t_range *range)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (str_len != 10 && str_len != 5 && str_len != 12)
		return (0);
	if (!ft_strncmp(str, "mandelbrot", 10) && argc == 2)
	{
		range->fractal = 0;
		return (1);
	}
	else if (!ft_strncmp(str, "julia", 5) && argc == 4)
	{
		range->fractal = 1;
		return (1);
	}
	else if (!ft_strncmp(str, "burning_ship", 12) && argc == 2)
	{
		range->fractal = 2;
		return (1);
	}
	else
		return (0);
}
