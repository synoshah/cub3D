
#include "include/image.h"
#include <stdlib.h>

void	my_pixel_put(t_data *img, int x, int y, int color);

void draw_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int	sx;
	int	sy;
	
	// Determine the direction of the step (-1 or 1)
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;

	// Initialize the error decision variable
	int err = dx - dy;

	while (1) {
		// Light up the current pixel
		my_pixel_put(img, x0, y0, color);

		// Break when the destination pixel is reached
		if (x0 == x1 && y0 == y1)
			break;
		// Multiply by 2 using a bit-shift for performance (e2 = 2 * err)
		int e2 = err << 1; 

		// Adjust coordinates based on the error margin
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}
