/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 22:55:37 by synoshah          #+#    #+#             */
/*   Updated: 2026/08/31 22:55:37 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray_step(t_context *ctx, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ctx->player->pypos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ctx->player->pypos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ctx->player->pypos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ctx->player->pypos_y)
			* ray->delta_dist_y;
	}
}

void	init_ray(t_context *ctx, t_ray *ray, int x)
{
	ray->camera_x = (2.0 * x / 800.0) - 1.0;
	ray->dir_x = ctx->player->dir_x + (ctx->player->camera_x * ray->camera_x);
	ray->dir_y = ctx->player->dir_y + (ctx->player->camera_y * ray->camera_x);
	ray->map_x = (int)ctx->player->pypos_x;
	ray->map_y = (int)ctx->player->pypos_y;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	init_ray_step(ctx, ray);
}

void	perform_dda(t_context *ctx, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0
			|| (size_t)ray->map_y >= ctx->map->size.height
			|| (size_t)ray->map_x >= ft_strlen(ctx->map->grid[ray->map_y]))
			ray->hit = 1;
		else if (ctx->map->grid[ray->map_y][ray->map_x] == '1'
			|| ctx->map->grid[ray->map_y][ray->map_x] == 'X')
			ray->hit = 1;
	}
}
