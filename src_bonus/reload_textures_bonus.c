/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 23:23:07 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/02 23:23:07 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	clear_textures(t_context *ctx)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ctx->textures[i].img)
			mlx_destroy_image(ctx->mlx, ctx->textures[i].img);
		ctx->textures[i].img = NULL;
		i++;
	}
}

static int	load_wall_textures(t_context *ctx)
{
	if (!load_texture(ctx->mlx, &ctx->textures[0],
			ctx->map->textures.north))
		return (0);
	if (!load_texture(ctx->mlx, &ctx->textures[1],
			ctx->map->textures.south))
		return (0);
	if (!load_texture(ctx->mlx, &ctx->textures[2],
			ctx->map->textures.east))
		return (0);
	if (!load_texture(ctx->mlx, &ctx->textures[3],
			ctx->map->textures.west))
		return (0);
	return (1);
}

static int	load_level_textures(t_context *ctx)
{
	char	*object_texture;

	if (ctx->game_state->level == 2)
		object_texture = "textures/throne.xpm";
	else if (ctx->game_state->level == 1)
		object_texture = "textures/boat.xpm";
	else
		object_texture = "textures/cave_exit.xpm";
	if (!load_texture(ctx->mlx, &ctx->textures[4], object_texture))
		return (0);
	if (ctx->game_state->level == 1
		&& !load_texture(ctx->mlx, &ctx->textures[5],
			"textures/natural_green_bamboo.xpm"))
		return (0);
	return (1);
}

int	reload_textures(t_context *ctx)
{
	clear_textures(ctx);
	if (!load_wall_textures(ctx))
		return (0);
	return (load_level_textures(ctx));
}
