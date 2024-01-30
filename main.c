#include "./minilibx-linux/mlx.h"
#include <stdlib.h>
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

    coordinates.real = (float) -2 + (x / width) * (1 - (-2));
    coordinates.img = (float) -1 + (y / height) * (1 - (-1));

    return (coordinates);
}

void    rectangle(t_data *img, int x, int y)
{
    int i;
    int j;
    t_complex   px_tst;
    t_complex   result;

    i = 0;
    while (i < y)
    {
        j = 0;
        while (j < x)
        {
            px_tst = pixel_to_complex(i, j, 800, 800);
            result = mandelbrot_recursive(4, px_tst);
            // printf("x %f y %f resul.real %f result.img %f\n", px_tst.real, px_tst.img, result.real, result.img);
            if ((result.real < 2  && result.real > -2) && (result.img < 2 && result.img > -2))
                my_mlx_px_put(img, i, j, 0x00FFFFFF);
            else
                my_mlx_px_put(img, i, j, 0x00000000);
            j++;
        }
        i++;
    }
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
    rectangle(img, 800, img->line_len);
    mlx_put_image_to_window(mlx, window, img->img, 0, 0);
	// img2.img = mlx_new_image(mlx, 400, 400);
    // img2.addr = mlx_get_data_addr(img2.img, &img2.bpp, &img2.line_len, &img2.endian);
    // rectangle(&img2, 150, 150, 0x00FF00FF);
    // mlx_put_image_to_window(mlx, window, img2.img, 100, 100);
	mlx_loop(mlx);
}
