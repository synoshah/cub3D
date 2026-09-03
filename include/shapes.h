#ifndef SHAPES_H
#define SHAPES_H

#include "image.h"
#include "draw.h"

void	draw_hexagon(t_data *img, int x, int y, int color, int radius);
void	draw_circle(t_data *img, t_point point, int color, int radius);
void	draw_square(t_data *img, t_point point, int color, int size);

#endif