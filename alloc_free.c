/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:15:49 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/19 17:16:32 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

int	**free_failed_alloc(int **tab, int i)
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
	tab = malloc(sizeof(double *) * height);
	if (!tab)
		return (NULL);
	while (i < height)
	{
		j = -1;
		tab[i] = malloc(sizeof(double) * width);
		while (++j < width)
			tab[i][j] = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}