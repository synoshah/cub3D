#include "include/shapes.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

void	draw_square(t_data *img, int x, int y, int color, int size)
{
	int	i;
	int	j;
	int	x_end;
	int	y_end;

	if (img == NULL || size <= 0)
		return ;
	x_end = x + size;
	y_end = y + size;
	i = x;
	while (i < x_end)
	{
		j = y;
		while (j < y_end)
		{
			my_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_circle(t_data *img, int xc, int yc, int color, int radius)
{
	int	y;
	int	x;
	int	d;

	x = 0;
	y = radius;
	d = 3 - 2 * radius;
	while (y >= x)
	{
		my_pixel_put(img, xc+x, yc + y, color);
		my_pixel_put(img, xc+x, yc - y, color);
		my_pixel_put(img, xc+y, yc + x, color);
		my_pixel_put(img, xc+y, yc - x, color);
		my_pixel_put(img, xc-x, yc + y, color);
		my_pixel_put(img, xc-x, yc - y, color);
		my_pixel_put(img, xc-y, yc + x, color);
		my_pixel_put(img, xc-y, yc - x, color);
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
	}
}
