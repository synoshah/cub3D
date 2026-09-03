/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_story.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 00:28:12 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/02 00:28:12 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	level_zero_text(t_context *ctx)
{
	mlx_string_put(ctx->mlx, ctx->mlx_win, 220, 250, 0xFFFFFF,
		"NOBODY HAS ESCAPED THE CAVE OF POLYPHEMUS.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 220, 280, 0xAAAAAA,
		"BUT POSEIDON HAS SHATTERED YOUR FLEET...");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 220, 330, 0xFF0000,
		"PRESS <'X'> TO WASH ASHORE ON CALYPSO'S ISLE.");
}

static void	level_one_text(t_context *ctx)
{
	mlx_string_put(ctx->mlx, ctx->mlx_win, 230, 250, 0xFFFFFF,
		"YOU HAVE CALYPSO'S SPELL. THE RAFT IS BUILT.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 230, 280, 0xAAAAAA,
		"YOU MUST RETURN HOME TO ITHACA.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 230, 330, 0xFF0000,
		"PRESS <'X'> TO FAST TRAVEL!");
}

static void	level_two_text(t_context *ctx)
{
	mlx_string_put(ctx->mlx, ctx->mlx_win, 240, 250, 0xFFFFFF,
		"YOU HAVE RECLAIMED THE THRONE OF ITHACA.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 255, 280, 0xAAAAAA,
		"THE LONG ODYSSEY IS FINALLY OVER.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 245, 330, 0x00FF00,
		"PRESS <'X'> TO CONCLUDE YOUR JOURNEY.");
}

static void	draw_story_text(t_context *ctx)
{
	if (ctx->game_state->level == 0)
		level_zero_text(ctx);
	else if (ctx->game_state->level == 1)
		level_one_text(ctx);
	else if (ctx->game_state->level == 2)
		level_two_text(ctx);
}

void	render_story(t_context *ctx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 800)
	{
		j = -1;
		while (++j < 600)
			my_pixel_put(ctx->img, i, j, 0x000000);
	}
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->img->img, 0, 0);
	draw_story_text(ctx);
}
