/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:27:58 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/20 17:55:47 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"
#include "math.h"

int     reverse_atoi_check(const char nptr, double nb)
{
    char *s1;
    char *s2;

    
}

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
            continue;
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

int main(int argc, char **argv)
{
    (void) argc;
    printf("nb = %f\n", ft_atoi_double(argv[1]));
}