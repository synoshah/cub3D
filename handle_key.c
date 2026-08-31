#include "cub3D.h"
#include "include/map.h"

// TODO: add state change from START -> PLAYING
int handle_key(t_context *ctx)
{
	t_player	*player = ctx->player;
	double		olddir_x = player->dir_x;
	double		olddir_y = player->dir_y;
	double		oldcam_x = player->camera_x;
	double		oldcam_y = player->camera_y;

	if (ctx->keys->w)
	{
		player->pypos_x = player->pypos_x + (player->dir_x * player->move_speed);
		player->pypos_y = player->pypos_y + (player->dir_y * player->move_speed);
		if ((int)player->pypos_x == 0)
		{
			ctx->game_state->gamemode = WON;
		}
		printf("Moving Forward %f, %f\n", player->pypos_x, player->pypos_y);    
	}
	if (ctx->keys->a)
	{
		player->pypos_x = player->pypos_x - (player->camera_x * player->move_speed);
		player->pypos_y = player->pypos_y - (player->camera_y * player->move_speed);
		printf("Moving Left %f, %f\n", player->pypos_x, player->pypos_y); 
	}
	if (ctx->keys->s)
	{
		player->pypos_x = player->pypos_x - (player->dir_x * player->move_speed);
		player->pypos_y = player->pypos_y - (player->dir_y * player->move_speed);
		printf("Moving Backward %f, %f\n", player->pypos_x, player->pypos_y); 
	}
	if (ctx->keys->d)
	{
		player->pypos_x = player->pypos_x + (player->camera_x * player->move_speed);
		player->pypos_y = player->pypos_y + (player->camera_y * player->move_speed);
		printf("Moving Right %f, %f\n", player->pypos_x, player->pypos_y); 
	}
	if (ctx->keys->r)
	{
		player->dir_x = (olddir_x * cos(player->rotation_speed) - (olddir_y * sin(player->rotation_speed)));
		player->dir_y = (olddir_x * sin(player->rotation_speed) + (olddir_y * cos(player->rotation_speed)));
		player->camera_x = (oldcam_x * cos(player->rotation_speed) - (oldcam_y * sin(player->rotation_speed)));
		player->camera_y = (oldcam_x * sin(player->rotation_speed) + (oldcam_y * cos(player->rotation_speed)));
	}
	if (ctx->keys->l)
	{
		player->dir_x = (olddir_x * cos(player->rotation_speed) + (olddir_y * sin(player->rotation_speed)));
		player->dir_y = -(olddir_x * sin(player->rotation_speed)) + (olddir_y * cos(player->rotation_speed));		
		player->camera_x = (oldcam_x * cos(player->rotation_speed) + (oldcam_y * sin(player->rotation_speed)));
		player->camera_y = -(oldcam_x * sin(player->rotation_speed)) + (oldcam_y * cos(player->rotation_speed));
	}
	if (ctx->game_state->gamemode == START && ctx->keys->w)
	{
		printf("changing state\n");
		ctx->game_state->gamemode = PLAYING;
		mlx_clear_window(ctx->mlx, ctx->mlx_win);
	}
	// else if (keycode == KEY_ESC)
	// {
	// 	printf("Close\n");
	// 	// mlx_destroy_image();
	// 	// mlx_clear_window();
	// 	// mlx_destroy_window();
	// 	exit(0);
	// }
	// clear_display(img);
	// draw_map(img);
	// draw_player(img, player);
	// mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, img->img, 0, 0);
	return 0;
}
