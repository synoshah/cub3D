/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 22:54:50 by synoshah          #+#    #+#             */
/*   Updated: 2026/08/31 22:54:50 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Comments for context

void	draw_start_text(t_context *ctx)
{
	mlx_string_put(ctx->mlx, ctx->mlx_win, 280, 250, 0xFFFFFF,
		"YOU ARE ODYSSEUS, KING OF ITHACA.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 278, 280, 0xAAAAAA,
		"TRAPPED IN THE CAVE OF POLYPHEMUS.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 260, 310, 0xAAAAAA,
		"THE CYCLOPS SLEEPS. YOU MUST FIND THE EXIT.");
	mlx_string_put(ctx->mlx, ctx->mlx_win, 290, 365, 0xFF0000,
		"PRESS <'W'> TO WAKE AND ESCAPE!");
}

void	render_start(t_context *ctx)
{
	static void	*title;
	int			w;
	int			h;
	int			i;
	int			j;

	if (!title)
		title = mlx_xpm_file_to_image(ctx->mlx, "textures/hii.xpm", &w, &h);
	i = -1;
	while (++i < 800)
	{
		j = -1;
		while (++j < 600)
			my_pixel_put(ctx->img, i, j, 0x000000);
	}
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->img->img, 0, 0);
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, title, 350, 150);
	draw_start_text(ctx);
}

void	render_playing(t_context *ctx)
{
	static int	frame = 0;
	t_data		temp;
	t_ray		ray;
	int			x;

	frame++;
	if (ctx->game_state->level == 1 && frame % 40 == 0)
	{
		temp = ctx->textures[0];
		ctx->textures[0] = ctx->textures[5];
		ctx->textures[5] = temp;
	}
	mlx_clear_window(ctx->mlx, ctx->mlx_win);
	draw_background(ctx->img, ctx->map->colors.ceiling,
		ctx->map->colors.floor);
	x = -1;
	while (++x < 800)
	{
		init_ray(ctx, &ray, x);
		perform_dda(ctx, &ray);
		calc_wall_height(&ray);
		get_texture_index(ctx, &ray);
		calc_texture_x(ctx, &ray);
		draw_wall_slice(ctx, &ray, x);
	}
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->img->img, 0, 0);
}

int	render_frame(t_context *ctx)
{
	handle_key(ctx);
	if (ctx->game_state->gamemode == START)
		render_start(ctx);
	else if (ctx->game_state->gamemode == PLAYING)
		render_playing(ctx);
	else if (ctx->game_state->gamemode == WON)
		load_next_level(ctx);
	else if (ctx->game_state->gamemode == DONE)
		render_end_screen(ctx);
	return (0);
}
