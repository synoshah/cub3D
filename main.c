#include "cub3D.h"

int handle_key(int keycode, t_player *player)
{
    double olddir_x = player->dir_x;
    double olddir_y = player->dir_y;
    double oldcam_x = player->camera_x;
    double oldcam_y = player->camera_y;
    if (keycode == KEY_W)
    {
        player->pypos_x = player->pypos_x + (player->dir_x * player->move_speed);
        player->pypos_y = player->pypos_y + (player->dir_y * player->move_speed);
        printf("Moving Forward %f, %f\n", player->pypos_x, player->pypos_y);    
    }
    else if (keycode == KEY_A)
    {
        player->pypos_x = player->pypos_x - (player->camera_x * player->move_speed);
        player->pypos_y = player->pypos_y - (player->camera_y * player->move_speed);
        printf("Moving Left %f, %f\n", player->pypos_x, player->pypos_y); 
    }
    else if (keycode == KEY_S)
    {
        player->pypos_x = player->pypos_x - (player->dir_x * player->move_speed);
        player->pypos_y = player->pypos_y - (player->dir_y * player->move_speed);
        printf("Moving Backward %f, %f\n", player->pypos_x, player->pypos_y); 
    }
    else if (keycode == KEY_D)
    {
        player->pypos_x = player->pypos_x + (player->camera_x * player->move_speed);
        player->pypos_y = player->pypos_y + (player->camera_y * player->move_speed);
        printf("Moving Right %f, %f\n", player->pypos_x, player->pypos_y); 
    }
    else if (keycode == KEY_RIGHT)
    {
        player->dir_x = (olddir_x * cos(player->rotation_speed) - (olddir_y * sin(player->rotation_speed)));
        player->dir_y = (olddir_x * sin(player->rotation_speed) + (olddir_y * cos(player->rotation_speed)));
        player->camera_x = (oldcam_x * cos(player->rotation_speed) - (oldcam_y * sin(player->rotation_speed)));
        player->camera_y = (oldcam_x * sin(player->rotation_speed) + (oldcam_y * cos(player->rotation_speed)));
    }
    else if (keycode == KEY_LEFT)
    {
        player->dir_x = (olddir_x * cos(player->rotation_speed) + (olddir_y * sin(player->rotation_speed)));
        player->dir_y = -(olddir_x * sin(player->rotation_speed) + (olddir_y * cos(player->rotation_speed)));
        player->camera_x = (oldcam_x * cos(player->rotation_speed) + (oldcam_y * sin(player->rotation_speed)));
        player->camera_y = -(oldcam_x * sin(player->rotation_speed) + (oldcam_y * cos(player->rotation_speed)));
    }
    else if (keycode == KEY_ESC)
    {
        printf("Close\n");
        exit(0);
    }
    return 0;
}

int rays(int x)
{
    int x = 0;
    while (x <= 800)
        x++;
    return x;
}

int close_game(t_player *player)
{
    printf("Game closed\n");
    exit(0);
    return (0);
}

int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_player 	player;
	t_data      img;

    player.pypos_x = 5.0; 
    player.pypos_y = 5.0;
    player.dir_x = 1.0;
    player.dir_y = 0.0;
    player.camera_x = 0.0;
    player.camera_y = 0.66;
    player.move_speed = 0.2;
    player.rotation_speed = 0.05;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "cub3D");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_hexagon(&img, 50, 50, 0x00FFFF, 50);
	draw_circle(&img, 100, 100, 0x554053, 100);
	draw_square(&img, 500, 500, 0x0F325478, 20);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	(void)mlx_win;
	mlx_key_hook(mlx_win, handle_key, &player);
	mlx_hook(mlx_win, 17, 0, close_game, &player);
	mlx_loop(mlx);
	return 0;
}
