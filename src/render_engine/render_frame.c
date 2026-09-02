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

int	render_frame(t_context *ctx)
{
	t_ray	ray;
	int		x;

	handle_key(ctx);
	mlx_clear_window(ctx->mlx, ctx->mlx_win);
	draw_background(ctx->img, ctx->map->colors.ceiling, ctx->map->colors.floor);
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
	return (0);
}
