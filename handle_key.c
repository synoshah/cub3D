#include "cub3D.h"
#include "include/map.h"

int handle_key(t_context *ctx)
{
	t_player	*player = ctx->player;
	double		olddir_x = player->dir_x;
	double		olddir_y = player->dir_y;
	double		oldcam_x = player->camera_x;
	double		oldcam_y = player->camera_y;

	if (ctx->keys->w)
	{
		double new_x = player->pypos_x + (player->dir_x * player->move_speed);
        double new_y = player->pypos_y + (player->dir_y * player->move_speed);
        if (ctx->map->grid[(int)player->pypos_y][(int)new_x] != '1')
            player->pypos_x = new_x;
        if (ctx->map->grid[(int)new_y][(int)player->pypos_x] != '1')
            player->pypos_y = new_y;
	}
	if (ctx->keys->a)
	{
		double new_x = player->pypos_x - (player->camera_x * player->move_speed);
		double new_y = player->pypos_y - (player->camera_y * player->move_speed);
        if (ctx->map->grid[(int)player->pypos_y][(int)new_x] != '1')
            player->pypos_x = new_x;
        if (ctx->map->grid[(int)new_y][(int)player->pypos_x] != '1')
            player->pypos_y = new_y;
	}
	if (ctx->keys->s)
	{
		double new_x = player->pypos_x - (player->dir_x * player->move_speed);
		double new_y = player->pypos_y - (player->dir_y * player->move_speed);
        if (ctx->map->grid[(int)player->pypos_y][(int)new_x] != '1')
            player->pypos_x = new_x;
        if (ctx->map->grid[(int)new_y][(int)player->pypos_x] != '1')
            player->pypos_y = new_y; 
	}
	if (ctx->keys->d)
	{
		double new_x = player->pypos_x + (player->camera_x * player->move_speed);
		double new_y = player->pypos_y + (player->camera_y * player->move_speed);
        if (ctx->map->grid[(int)player->pypos_y][(int)new_x] != '1')
            player->pypos_x = new_x;
        if (ctx->map->grid[(int)new_y][(int)player->pypos_x] != '1')
            player->pypos_y = new_y; 
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
