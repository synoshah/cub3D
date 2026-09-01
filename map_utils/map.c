
#include "include/draw.h"
#include "include/shapes.h"
#include "../cub3D.h"

#define HEIGHT 24
#define WIDTH 24

void draw_background(t_data *img, int ceiling_color, int floor_color)
{
	int x;
	int y;

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

void	draw_map(t_map *map, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)map->size.height)
	{
		j = 0;
		while (j < (int)map->size.width)
		{
			draw_square(img, j , i , 0xFFFFFF, 5);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *img, t_player *player)
{
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	
	start_x = 20 + (int)(player->pypos_x * 8);
	start_y = 20 + (int)(player->pypos_y * 8);
	end_x = start_x + (int)(player->dir_x * 5);
	end_y = start_y + (int)(player->dir_y * 5);
	draw_line(img, start_x, start_y, end_x, end_y, 0x00FF00);
}

void draw_minimap(t_context *ctx)
{
	int tile;
	int offset_x;
	int offset_y;
	int x;
	int y;

	tile = 7;
	offset_x = 10;
	offset_y = 10;

	y = 0;
	while (y < (int)ctx->map->size.height)
	{
		x = 0;
		while (x < (int)ctx->map->size.width)
		{
			if (ctx->map->grid[y][x] == 'V')
				draw_square(ctx->img, offset_x + x * tile,
					offset_y + y * tile, 0, tile);
			else
				draw_square(ctx->img, offset_x + x * tile,
					offset_y + y * tile, 0x222222, tile);
			x++;
		}
		y++;
	}
	draw_player(ctx->img, ctx->player);
}