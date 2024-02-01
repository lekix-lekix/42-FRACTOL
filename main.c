#include "./minilibx-linux/mlx.h"
#include <stdlib.h>
#include "math.h"
#include "./fractol.h"
#include <stdio.h>

void    my_mlx_px_put(t_data *img, int x, int y, int color)
{
    char *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}

t_complex   pixel_to_complex(int x, int y, int height, int width)
{
    t_complex coordinates;
    float x_percent;
    float y_percent;
    
    x_percent = (float) x / (float) width;
    y_percent = (float) y / (float) height;

    coordinates.real = -2 + (2 - (-2)) * x_percent;
    coordinates.img = -2 + (2 - (-2)) * y_percent;

    return (coordinates);
}



void    rectangle(t_data *img, int max_iter, int width, int height)
{
    int i;
    int j;
    int mandel_i;
    int *color_tab;
    t_complex   px_tst;

    i = 0;
    mandel_i = 0;
    color_tab = malloc(sizeof(int) * max_iter);
    if (!color_tab)
        return ;
    while (i < max_iter)
    { 
        color_tab[i] = 0;
        i++;
    }
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            px_tst = pixel_to_complex(i, j, height, width);
            mandel_i = mandelbrot(max_iter, px_tst);
            color_tab[mandel_i]++;
            printf("%d\n", mandel_i);
            // if (mandel_i == max_iter)
            //     my_mlx_px_put(img, i, j, 0x00000000);
            // else if (mandel_i > 5 && mandel_i < max_iter)
            //     my_mlx_px_put(img, i, j, 0x00FFFFFF);
            // else
            //     my_mlx_px_put(img, i, j, 0x00000099);
            j++;
        }
        i++;
    }
    // i = 0;
    // int total = 0;
    // while (i < max_iter)
    // {
    //     total += color_tab[i];
    //     printf("color tab %d = %d\n", i, color_tab[i]);
    //     i++;
    // }
    // printf("total = %d\n", total);
}

t_data  *create_image(void *mlx, int width, int height)
{
    t_data *img;

    img = malloc(sizeof(t_data));
    if (!img)
        return (NULL);
    img->img = mlx_new_image(mlx, width, height);
    if (!(img->img))
        return (NULL);
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
    return (img);
}

int	main(void)
{
	void *mlx;
	void *window;
	t_data *img;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, 800, 800, "wesh la zone");
	if (!window)
		return (-1);
    img = NULL;
	img = create_image(mlx, 800, 800);
    if (!img)
        return (-1);
    printf("img bpp %d, len %d, endian %d\n", img->bpp, img->line_len, img->endian);
    rectangle(img, 10, 800, 800);
    mlx_put_image_to_window(mlx, window, img->img, 0, 0);
	mlx_loop(mlx);
    t_complex px;

    px = pixel_to_complex(100, 100, 800, 800);
    printf("reel %f img %f\n", px.real, px.img);
}
