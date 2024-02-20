/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palettes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:16:30 by kipouliq          #+#    #+#             */
/*   Updated: 2024/02/20 10:53:40 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

void    palette_one(int *colors)
{
    colors[0] = create_trgb(0, 250, 190, 11);
    colors[1] = create_trgb(0, 251, 86, 7);
    colors[2] = create_trgb(0, 255, 0, 110);    // rainbow
    colors[3] = create_trgb(0, 131, 56, 236);
    colors[4] = create_trgb(0, 58, 134, 255);
}

void    palette_two(int *colors)
{
    colors[0] = create_trgb(0, 155, 93, 229);
    colors[1] = create_trgb(0, 241, 91, 181);
    colors[2] = create_trgb(0, 254, 228, 64);       // candy
    colors[3] = create_trgb(0, 0, 187, 249);
    colors[4] = create_trgb(0, 0, 245, 212);
}

void    palette_three(int *colors)
{
    colors[0] = create_trgb(0, 157, 2, 8);
    colors[1] = create_trgb(0, 220, 47, 2);
    colors[2] = create_trgb(0, 254, 228, 64);
    colors[3] = create_trgb(0, 232, 93, 4);         // burning
    colors[4] = create_trgb(0, 255, 186, 8);    
    
}

void    palette_four(int *colors)
{
    colors[0] = create_trgb(0, 33, 5, 53);
    colors[1] = create_trgb(0, 67, 13, 75);
    colors[2] = create_trgb(0, 123, 51, 125);
    colors[3] = create_trgb(0, 200, 116, 178);
    colors[4] = create_trgb(0, 245, 213, 224);      // purple haze
}


