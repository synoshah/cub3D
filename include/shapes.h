
#ifndef SHAPES_H
#define SHAPES_H

#include "image.h"


void	my_pixel_put(t_data *img, int x, int y, int color);
void 	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);

void	draw_hexagon(t_data *img, int x, int y, int color, int radius);
void	draw_circle(t_data *img, int x, int y, int color, int radius);
void	draw_square(t_data *img, int x, int y, int color, int size);

#endif