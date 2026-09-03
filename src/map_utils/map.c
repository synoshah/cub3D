#include "cub3D.h"

void	draw_background(t_data *img, int ceiling_color, int floor_color)
{
	int	x;
	int	y;

	x = 0;
	while (x < 800)
	{
		y = 0;
		while (y < 600)
		{
			if (y < 300)
				my_pixel_put(img, x, y, ceiling_color);
			else
				my_pixel_put(img, x, y, floor_color);
			y++;
		}
		x++;
	}
}
