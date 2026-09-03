
#ifndef DRAW_H
#define DRAW_H

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

#include "image.h"

void	draw_line(t_data *img, t_point start, t_point end, int color);
void	my_pixel_put(t_data *img, int x, int y, int color);
int     get_texture_pixel(t_data *texture, int x, int y);

#endif
