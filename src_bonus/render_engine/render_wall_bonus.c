/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 22:54:56 by synoshah          #+#    #+#             */
/*   Updated: 2026/08/31 22:54:56 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist <= 0.0001)
		ray->perp_wall_dist = 0.0001;
	ray->line_height = (int)(600 / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + 600 / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + 600 / 2;
	if (ray->draw_end >= 600)
		ray->draw_end = 599;
}

void	get_texture_index(t_context *ctx, t_ray *ray)
{
	if (ctx->map->grid[ray->map_y][ray->map_x] == 'X')
		ray->tex_index = 4;
	else if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->tex_index = 2;
		else
			ray->tex_index = 3;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->tex_index = 1;
		else
			ray->tex_index = 0;
	}
}

void	calc_texture_x(t_context *ctx, t_ray *ray)
{
	t_data	*tex;
	
	tex = &ctx->textures[ray->tex_index];
	if (ray->side == 0)
		ray->wall_x = ctx->player->pypos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = ctx->player->pypos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	ray->step = 1.0 * tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - 600 / 2 + ray->line_height / 2) * ray->step;
}

void	draw_wall_slice(t_context *ctx, t_ray *ray, int x)
{
	int		y;
	t_data	*tex;

	y = ray->draw_start;
	tex = &ctx->textures[ray->tex_index];
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos;
		if (ray->tex_y >= tex->height)
			ray->tex_y = tex->height - 1;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		ray->tex_pos += ray->step;
		ray->color = get_texture_pixel(tex, ray->tex_x, ray->tex_y);
		if (ray->side == 1)
			ray->color = (ray->color >> 1) & 0x7F7F7F;
		my_pixel_put(ctx->img, x, y, ray->color);
		y++;
	}
}
