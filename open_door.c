#include "cub3D.h"

void	toggle_door(t_context *ctx)
{
	int         x;
	int         y;

	x = (int)(ctx->player->pypos_x + ctx->player->dir_x * 0.5);
	y = (int)(ctx->player->pypos_y + ctx->player->dir_y * 0.5);
	if (ctx->map->grid[y][x] == 'X')
		ctx->map->grid[y][x] = '0';
	else if(ctx->map->grid[y][x] == '0')
		ctx->map->grid[y][x] = 'X';
}
