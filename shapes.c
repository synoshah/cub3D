
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
