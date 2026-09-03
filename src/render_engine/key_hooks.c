/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:17:21 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/02 19:17:21 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_key_press(int keycode, t_context *ctx)
{
	if (keycode == KEY_ESC)
		close_game(ctx);
	if (keycode == KEY_W)
		ctx->keys->w = 1;
	if (keycode == KEY_S)
		ctx->keys->s = 1;
	if (keycode == KEY_A)
		ctx->keys->a = 1;
	if (keycode == KEY_D)
		ctx->keys->d = 1;
	if (keycode == KEY_LEFT)
		ctx->keys->l = 1;
	if (keycode == KEY_RIGHT)
		ctx->keys->r = 1;
	return (0);
}

int	handle_key_release(int keycode, t_context *ctx)
{
	if (keycode == KEY_W)
		ctx->keys->w = 0;
	if (keycode == KEY_S)
		ctx->keys->s = 0;
	if (keycode == KEY_A)
		ctx->keys->a = 0;
	if (keycode == KEY_D)
		ctx->keys->d = 0;
	if (keycode == KEY_LEFT)
		ctx->keys->l = 0;
	if (keycode == KEY_RIGHT)
		ctx->keys->r = 0;
	return (0);
}
