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

int	reload_textures(t_context *ctx)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (ctx->textures[i].img)
			mlx_destroy_image(ctx->mlx, ctx->textures[i].img);
		ctx->textures[i].img = NULL;
	}
	if (!load_texture(ctx->mlx, &ctx->textures[0], ctx->map->textures.north)) return (0);
	if (!load_texture(ctx->mlx, &ctx->textures[1], ctx->map->textures.south)) return (0);
	if (!load_texture(ctx->mlx, &ctx->textures[2], ctx->map->textures.east)) return (0);
	if (!load_texture(ctx->mlx, &ctx->textures[3], ctx->map->textures.west)) return (0);
	
	if (ctx->game_state->level == 2)
	{
		if (!load_texture(ctx->mlx, &ctx->textures[4], "textures/throne.xpm")) return (0);
	}
	else if (ctx->game_state->level == 1)
	{
		if (!load_texture(ctx->mlx, &ctx->textures[4], "textures/boat.xpm")) return (0);
	}
	else
	{
		if (!load_texture(ctx->mlx, &ctx->textures[4], "textures/cave_exit.xpm")) return (0);
	}
	
	if (ctx->game_state->level == 1)
	{
		if (!load_texture(ctx->mlx, &ctx->textures[5], "textures/natural_green_bamboo.xpm")) return (0);
	}
	return (1);
}

int	load_next_level(t_context *ctx)
{
	ctx->game_state->level++;
	if (ctx->game_state->level > 2)
	{
		ctx->game_state->gamemode = DONE;
		return (0);
	}
	free_map(ctx->map);
	if (ctx->game_state->level == 1)
		ctx->map = parse_map_file("maps/map2.cub");
	else if (ctx->game_state->level == 2)
		ctx->map = parse_map_file("maps/map3.cub");
	
	if (!ctx->map)
	{
		printf("Error\nFailed to parse map\n");
		return (0);
	}
	if (!reload_textures(ctx))
		return (0);
		
	ctx->player->pypos_x = ctx->map->spawn.x + 0.1;
	ctx->player->pypos_y = ctx->map->spawn.y + 0.1;
	reset_player_dir(ctx->player, ctx->map->spawn.direction);
	ctx->game_state->gamemode = PLAYING;
	return (1);
}

void	render_end_screen(t_context *ctx)
{
	int	w;
	int	h;

	if (!ctx->end_img)
		ctx->end_img = mlx_xpm_file_to_image(ctx->mlx, "textures/end_screen.xpm", &w, &h);
	if (ctx->end_img)
		mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->end_img, 0, 0);
}
