#include "include/draw.h"
#include "include/shapes.h"
#include "../../cub3D.h"

#define HEIGHT 24
#define WIDTH 24

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

void	draw_minimap(t_context *ctx)
{
	int		tile;
	t_point	offset;
	t_point	point;
	int		x;
	int		y;

	tile = 7;
	offset.x = 10;
	offset.y = 10;
	y = -1;
	printf("%ld %ld\n", ctx->map->size.height, ctx->map->size.width);
	while (y++ < (int)ctx->map->size.height)
	{
		x = -1;
		while ((int)ft_strlen(ctx->map->grid[y]) >= 0 && x++ < (int)ft_strlen(ctx->map->grid[y]))
		{
			point.x = offset.x + x * tile;
			point.y = offset.y + y * tile;
			if (ctx->map->grid[y][x] == 'V')
				draw_square(ctx->img, point, 0, tile);
			else
				draw_square(ctx->img, point, 0x222222, tile);
		}
	}
	draw_player(ctx->img, ctx->player);
}
