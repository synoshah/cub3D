/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:45:05 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/04 15:30:04 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_game(t_context *ctx)
{
	int	i;

	i = -1;
	if (ctx->map)
		free_map(ctx->map);
	if (ctx->img && ctx->img->img)
		mlx_destroy_image(ctx->mlx, ctx->img->img);
	while (++i < 4)
	{
		if (ctx->textures[i].img)
			mlx_destroy_image(ctx->mlx, ctx->textures[i].img);
	}
	if (ctx->mlx_win)
		mlx_destroy_window(ctx->mlx, ctx->mlx_win);
	if (ctx->mlx)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
	exit(0);
	return (0);
}

static int	init_map_and_player(t_context *ctx, char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (0);
	ctx->map = parse_map_file(file);
	if (!ctx->map)
		return (0);
	ctx->player->pypos_x = ctx->map->spawn.x + 0.1;
	ctx->player->pypos_y = ctx->map->spawn.y + 0.1;
	ctx->player->move_speed = 0.03;
	ctx->player->rotation_speed = 0.02;
	reset_player_dir(ctx->player, ctx->map->spawn.direction);
	return (1);
}

static int	setup_mlx(t_context *ctx, t_data *img)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		close_game(ctx);
	ctx->mlx_win = mlx_new_window(ctx->mlx, 800, 600, "cub3D");
	if (!ctx->mlx_win)
		close_game(ctx);
	img->img = mlx_new_image(ctx->mlx, 800, 600);
	if (!img->img)
		close_game(ctx);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ctx->img = img;
	if (!load_texture(ctx->mlx, &ctx->textures[0], ctx->map->textures.north))
		close_game(ctx);
	if (!load_texture(ctx->mlx, &ctx->textures[1], ctx->map->textures.south))
		close_game(ctx);
	if (!load_texture(ctx->mlx, &ctx->textures[2], ctx->map->textures.east))
		close_game(ctx);
	if (!load_texture(ctx->mlx, &ctx->textures[3], ctx->map->textures.west))
		close_game(ctx);
	return (1);
}

static void	register_hooks_and_loop(t_context *ctx)
{
	mlx_loop_hook(ctx->mlx, render_frame, ctx);
	mlx_hook(ctx->mlx_win, 2, 1L << 0, handle_key_press, ctx);
	mlx_hook(ctx->mlx_win, 3, 1L << 1, handle_key_release, ctx);
	mlx_hook(ctx->mlx_win, 17, 0, close_game, ctx);
	mlx_loop(ctx->mlx);
}

int	main(int argc, char **argv)
{
	t_context	ctx;
	t_player	p;
	t_input		in;
	t_data		img;

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments.\n");
		return (1);
	}
	ft_memset(&ctx, 0, sizeof(t_context));
	ft_memset(&p, 0, sizeof(t_player));
	ft_memset(&in, 0, sizeof(t_input));
	ctx.player = &p;
	ctx.keys = &in;
	if (!init_map_and_player(&ctx, argv[1]))
	{
		printf("Error\nFailed to load map.\n");
		return (1);
	}
	setup_mlx(&ctx, &img);
	register_hooks_and_loop(&ctx);
	return (0);
}
