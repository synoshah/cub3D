/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:09:01 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:09:02 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/draw.h"
#include <stdlib.h>

void	my_pixel_put(t_data *img, int x, int y, int color);

int	get_texture_pixel(t_data *texture, int x, int y)
{
	char	*pixel_address;
	int		color;

	pixel_address = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel_address;
	return (color);
}

static void	step_line(t_point *start, t_point end,
		t_point delta, int *err)
{
	int	error;

	error = 2 * *err;
	if (error > -delta.y)
	{
		*err -= delta.y;
		if (start->x < end.x)
			start->x += 1;
		else
			start->x -= 1;
	}
	if (error < delta.x)
	{
		*err += delta.x;
		if (start->y < end.y)
			start->y += 1;
		else
			start->y -= 1;
	}
}

void	draw_line(t_data *img, t_point start, t_point end, int color)
{
	t_point	delta;
	int		err;

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	err = delta.x - delta.y;
	while (1)
	{
		my_pixel_put(img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		step_line(&start, end, delta, &err);
	}
}
