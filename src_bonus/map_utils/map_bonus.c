/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:06:23 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 22:17:17 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/draw.h"
#include "include/shapes.h"
#include "cub3D_bonus.h"

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

void	draw_player(t_data *img, t_player *player)
{
	t_point	start;
	t_point	end;

	start.x = 10 + (int)(player->pypos_x * 7);
	start.y = 10 + (int)(player->pypos_y * 7);
	end.x = start.x + (int)(player->dir_x * 5);
	end.y = start.y + (int)(player->dir_y * 5);
	draw_line(img, start, end, 0x00FF00);
}

static void	draw_minimap_row(t_context *ctx, int y, int tile, t_point offset)
{
	int		x;
	t_point	point;

	x = 0;
	while (ctx->map->grid[y][x] != '\0')
	{
		point.x = offset.x + x * tile;
		point.y = offset.y + y * tile;
		if (ctx->map->grid[y][x] == 'V')
			draw_square(ctx->img, point, 0, tile);
		else
			draw_square(ctx->img, point, 0x222222, tile);
		x++;
	}
}

void	draw_minimap(t_context *ctx)
{
	int		tile;
	t_point	offset;
	int		y;

	tile = 7;
	offset.x = 10;
	offset.y = 10;
	y = 0;
	while (y < (int)ctx->map->size.height)
	{
		if (!ctx->map->grid[y])
			break ;
		draw_minimap_row(ctx, y, tile, offset);
		y++;
	}
	draw_player(ctx->img, ctx->player);
}
