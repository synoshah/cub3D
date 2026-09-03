/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:06:50 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 22:20:10 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
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
