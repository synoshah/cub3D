#include "cub3D.h"
#include "include/shapes.h"
#include "include/draw.h"
#define _USE_MATH_DEFINES
#include <math.h>

static void	draw_circle_step(t_data *img, t_point point, t_point p, int color)
{
	my_pixel_put (img, point.x + p.x, point.y + p.y, color);
	my_pixel_put (img, point.x + p.x, point.y - p.y, color);
	my_pixel_put (img, point.x + p.y, point.y + p.x, color);
	my_pixel_put (img, point.x + p.y, point.y - p.x, color);
	my_pixel_put (img, point.x - p.x, point.y + p.y, color);
	my_pixel_put (img, point.x - p.x, point.y - p.y, color);
	my_pixel_put (img, point.x - p.y, point.y + p.x, color);
	my_pixel_put (img, point.x - p.y, point.y - p.x, color);
}

void	draw_circle(t_data *img, t_point point, int color, int radius)
{
	t_point	p;
	int		d;

	p.x = 0;
	p.y = radius;
	d = 3 - 2 * radius;
	while (p.y >= p.x)
	{
		draw_circle_step(img, point, p, color);
		p.x++;
		if (d > 0)
		{
			p.y--;
			d = d + 4 * (p.x - p.y) + 10;
		}
		else
			d = d + 4 * p.x + 6;
	}
}

void	draw_square(t_data *img, t_point point, int color, int size)
{
	int	i;
	int	j;
	int	x_end;
	int	y_end;

	if (img == NULL || size <= 0)
		return ;
	x_end = point.x + size;
	y_end = point.y + size;
	i = point.x;
	while (i < x_end)
	{
		j = point.y;
		while (j < y_end)
		{
			my_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}
