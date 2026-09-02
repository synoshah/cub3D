/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 22:59:07 by synoshah          #+#    #+#             */
/*   Updated: 2026/08/31 22:59:07 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D.h"

static void	move_player(t_context *ctx, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = ctx->player->pypos_x + move_x;
	new_y = ctx->player->pypos_y + move_y;
	if (new_y >= 0 && (size_t)new_y < ctx->map->size.height)
	{
		if (new_x >= 0 && (size_t)new_x < ft_strlen(ctx->map->grid[(int)new_y]))
		{
			if (ctx->map->grid[(int)new_y][(int)new_x] != '1')
			{
				ctx->player->pypos_x = new_x;
				ctx->player->pypos_y = new_y;
			}
		}
	}
}

static void	rotate_player(t_player *p, double rot_speed)
{
	double	old_dir_x;
	double	old_cam_x;

	old_dir_x = p->dir_x;
	old_cam_x = p->camera_x;
	p->dir_x = old_dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
	p->camera_x = old_cam_x * cos(rot_speed) - p->camera_y * sin(rot_speed);
	p->camera_y = old_cam_x * sin(rot_speed) + p->camera_y * cos(rot_speed);
}

int	handle_key(t_context *ctx)
{
	t_player	*p;

	p = ctx->player;
	if (ctx->keys->w)
		move_player(ctx, p->dir_x * p->move_speed, p->dir_y * p->move_speed);
	if (ctx->keys->s)
		move_player(ctx, -p->dir_x * p->move_speed, -p->dir_y * p->move_speed);
	if (ctx->keys->a)
		move_player(ctx, -p->camera_x * p->move_speed, -p->camera_y * p->move_speed);
	if (ctx->keys->d)
		move_player(ctx, p->camera_x * p->move_speed, p->camera_y * p->move_speed);
	if (ctx->keys->r)
		rotate_player(ctx->player, ctx->player->rotation_speed);
	if (ctx->keys->l)
		rotate_player(ctx->player, -ctx->player->rotation_speed);
	return (0);
}
