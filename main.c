#include "./minilibx-linux/mlx.h"
#include <stdlib.h>
#include "math.h"
#include "./fractol.h"
#include <stdio.h>

int **free_failed_alloc(int **tab, int i)
{
    while (i >= 0)
    {
        free(tab[i]);
        i--;
    }
    free(tab);
    return (NULL);
}

int *ft_free_tab(int **tab, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

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

int **ft_alloc_tab(int width, int height)
{
    int **tab;
    int i;

    i = 0;
    tab = malloc(sizeof(int *) * height);
    if (!tab)
        return (NULL);
    while (i < width)
    {
        tab[i] = malloc(sizeof(int) * width);
        if (!tab[i])
            return (free_failed_alloc(tab, i));
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

float **ft_alloc_tab_float(int width, int height)
{
    float **tab;
    int i;

    i = 0;
    tab = malloc(sizeof(float *) * height);
    if (!tab)
        return (NULL);
    while (i < width)
    {
        tab[i] = malloc(sizeof(float) * width);
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

void    rectangle(t_data *img, int max_iter, int width, int height)
{
    int i;
    int j;
    int mandel_i;
    int *color_tab;
    float **px_hue;
    int **px_iter;
    t_complex   px_tst;

    i = 0;
    mandel_i = 0;
    color_tab = malloc(sizeof(int) * max_iter);
    if (!color_tab)
        return ;
    px_iter = ft_alloc_tab(width, height);
    if (!px_iter)
        return ; // need to free color_tab
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
            color_tab[mandel_i - 1]++;
            px_iter[i][j] = mandel_i;
            printf("%d\n", px_iter[i][j]);
            // if (mandel_i == max_iter)
            //     my_mlx_px_put(img, i, j, 0x00000000);
            // else if (mandel_i > 5 && mandel_i < max_iter)
                // my_mlx_px_put(img, i, j, 0x00FFFFFF);
            // else
            //     my_mlx_px_put(img, i, j, 0x00000099);
            j++;
        }
        i++;
    }
    int k;
    float hue;
    px_hue = ft_alloc_tab_float(width, height);
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            hue = 0;
            k = 0;
            while (k <= px_iter[i][j])
            {
                // printf("pxiter = %d\n", px_iter[i][j]);
                // printf("color tab[k] = %d\n", color_tab[k]);
                // printf("color tab[%d] = %d, width * height = %d, div = %f\n", k, color_tab[k], width * height, (float)color_tab[k] / (width * height));
                px_hue[i][j] += (float) color_tab[k] / ((float)width * (float)height);
                k++;
                // printf("hue = %f\n", hue);
            }
            j++;
        }
        i++;
    }
    i = 0;
    j = 0;
    float max = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (px_hue[i][j] > max)
                max = px_hue[i][j];
            printf("px hue [%d][%d] = %f\n", i, j, px_hue[i][j]);
            j++;
        }
        i++;
    }
    printf("height = %d\n", height);
    printf("max = %f\n", max);
    ft_free_tab(px_iter, height);
    free(color_tab);
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
    // printf("img bpp %d, len %d, endian %d\n", img->bpp, img->line_len, img->endian);
    rectangle(img, 10, 800, 800);
    // mlx_put_image_to_window(mlx, window, img->img, 0, 0);
    free(img);
    mlx_destroy_window(mlx, window);
	// mlx_loop(mlx);
}
