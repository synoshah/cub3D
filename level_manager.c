/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 22:55:15 by synoshah          #+#    #+#             */
/*   Updated: 2026/08/31 22:55:15 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	reset_player_dir(t_player *player, char dir)
{
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->camera_x = 0.0;
	player->camera_y = 0.0;
	if (dir == 'N')
	{
		player->dir_y = -1.0;
		player->camera_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1.0;
		player->camera_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1.0;
		player->camera_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1.0;
		player->camera_y = -0.66;
	}
}

void	reload_textures(t_context *ctx)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (ctx->textures[i].img)
			mlx_destroy_image(ctx->mlx, ctx->textures[i].img);
	}
	load_texture(ctx->mlx, &ctx->textures[0], ctx->map->textures.north);
	load_texture(ctx->mlx, &ctx->textures[1], ctx->map->textures.south);
	load_texture(ctx->mlx, &ctx->textures[2], ctx->map->textures.east);
	load_texture(ctx->mlx, &ctx->textures[3], ctx->map->textures.west);
	load_texture(ctx->mlx, &ctx->textures[4], "textures/cave_exit.xpm");
}

void	load_next_level(t_context *ctx)
{
	ctx->game_state->level++;
	if (ctx->game_state->level > 2)
	{
		ctx->game_state->gamemode = DONE;
		return ;
	}
	free_map(ctx->map);
	if (ctx->game_state->level == 1)
		ctx->map = parse_map_file("maps/map2.cub");
	else if (ctx->game_state->level == 2)
		ctx->map = parse_map_file("maps/map3.cub");
	if (!ctx->map)
	{
		printf("failed to parse map\n");
		exit(1);
	}
	reload_textures(ctx);
	ctx->player->pypos_x = ctx->map->spawn.x + 0.1;
	ctx->player->pypos_y = ctx->map->spawn.y + 0.1;
	reset_player_dir(ctx->player, ctx->map->spawn.direction);
	ctx->game_state->gamemode = PLAYING;
}

void	render_end_screen(t_context *ctx)
{
	static void	*end_img = NULL;
	int			w;
	int			h;

	if (!end_img)
		end_img = mlx_xpm_file_to_image(ctx->mlx,
				"textures/end_screen.xpm", &w, &h);
	if (end_img)
		mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, end_img, 0, 0);
}
