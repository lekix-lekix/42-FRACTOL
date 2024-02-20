/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:15:49 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/20 14:36:38 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

double	**free_failed_alloc(double **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

int	*ft_free_tab(double **tab, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

double	**ft_alloc_tab_double(int width, int height)
{
	int		i;
	int		j;
	double	**tab;

	i = 0;
	tab = malloc(sizeof(double *) * (height + 1));
	if (!tab)
		return (NULL);
	while (i < height)
	{
		j = -1;
		tab[i] = malloc(sizeof(double) * width);
		if (!tab[i])
			return (free_failed_alloc(tab, i), NULL);
		while (++j < width)
			tab[i][j] = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_free_mlx(t_mlx_win *data)
{
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (-1);
}
