
#include "include/shapes.h"
#define _USE_MATH_DEFINES
#include <math.h>

void	my_pixel_put(t_data *img, int x, int y, int color);
void 	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);


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

void	draw_square(t_data *img, int x, int y, int color, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_hexagon(t_data *img, int x, int y, int color, int radius)
{
	int	i;
    int x_coords[6];
    int y_coords[6];

    // 1. Calculate the 6 vertices
	i = 0;
	while (i < 6)
	{
        // 60 degrees in radians is i * (2 * PI / 6) = i * PI / 3
        double angle = i * M_PI / 3.0; 
        
        // Round to nearest integer pixel
        x_coords[i] = x + (int)round(radius * cos(angle));
        y_coords[i] = y + (int)round(radius * sin(angle));
		i++;
	}

    // 2. Connect the vertices with lines
	i = 0;
	while (i < 6)
	{
        int next = (i + 1) % 6;
        draw_line(img, x_coords[i], y_coords[i], x_coords[next], y_coords[next], color);
		i++;
    }

}
