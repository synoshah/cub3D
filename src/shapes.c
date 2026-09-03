/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:13:52 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:13:53 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "include/shapes.h"
#include "include/draw.h"
#define _USE_MATH_DEFINES
#include <math.h>

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
