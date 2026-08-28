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
		player->pypos_x = player->pypos_x + (player->dir_x * player->move_speed);
		player->pypos_y = player->pypos_y + (player->dir_y * player->move_speed);
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
	if (ctx->keys->l)
	{
		player->dir_x = (olddir_x * cos(player->rotation_speed) - (olddir_y * sin(player->rotation_speed)));
		player->dir_y = (olddir_x * sin(player->rotation_speed) + (olddir_y * cos(player->rotation_speed)));
		player->camera_x = (oldcam_x * cos(player->rotation_speed) - (oldcam_y * sin(player->rotation_speed)));
		player->camera_y = (oldcam_x * sin(player->rotation_speed) + (oldcam_y * cos(player->rotation_speed)));
	}
	if (ctx->keys->r)
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

int	handle_key_press(int keycode, t_context *ctx)
{
	printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
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
	printf("%d\n", ctx->keys->w);
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
	printf("%d\n", ctx->keys->w);
	
	return (0);
}

int close_game(t_context *player)
{
	(void)player;
	printf("Game closed\n");
	exit(0);
	return (0);
}

int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_player 	player = {0};
	t_data      img;
	t_map		*map;

	map = parse_cub_file("maps/map1.cub");
	if (!map)
	{
		printf("failed to parse map.\n");
		return (1);
	}
	// spawn in the center of the grid
	player.pypos_x = map->spawn.x + 0.5;
	player.pypos_y = map->spawn.y + 0.5;

	// set vectors for spawn direction
	if (map->spawn.direction == 'N')
	{
		player.dir_x = 0.0;
		player.dir_y = -1.0;
		player.camera_x = 0.66;
		player.camera_y = 0.0;
	}
	else if (map->spawn.direction == 'S')
	{
		player.dir_x = 0.0;
		player.dir_y = 1.0;
		player.camera_x = -0.66;
		player.camera_y = 0.0;
	}
	else if (map->spawn.direction == 'E')
	{
		player.dir_x = 1.0;
		player.dir_y = 0.0;
		player.camera_x = 0.0;
		player.camera_y = 0.66;
	}
	else if (map->spawn.direction == 'W')
	{
		player.dir_x = -1.0;
		player.dir_y = 0.0;
		player.camera_x = 0.0;
		player.camera_y = -0.66;
	}
	player.pypos_x = 5.0; 
	player.pypos_y = 5.0;
	player.dir_x = 0.0;
	player.dir_y = -1.0;
	player.camera_x = 0.66;
	player.camera_y = 0.0;
	player.move_speed = 0.1;
	player.rotation_speed = 0.01;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "cub3D");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	(void)mlx_win;
	// Testing new struct...
	t_input		input = {0};
	t_context   ctx = {&player, &img, mlx, mlx_win, &input, map};
	mlx_loop_hook(mlx, render_frame, &ctx);
	// Key press and key release events
	mlx_hook(mlx_win, 2, 1L<<0,  handle_key_press, &ctx);
	mlx_hook(mlx_win, 3, 1L<<1 ,handle_key_release, &ctx);
	mlx_do_key_autorepeatoff(mlx); // Idk what this does lol.
	mlx_hook(mlx_win, 17, 0, close_game, &ctx);
	mlx_loop(mlx);
	return 0;
}
