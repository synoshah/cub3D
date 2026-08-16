#include "cub3D.h"

int handle_key(int keycode, t_player *player)
{
    double olddir_x = player->dir_x;
    double olddir_y = player->dir_y;
    // double oldcam_x = player->camera_x;
    // double oldcam_y = player->camera_y;
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
        printf("Moving Left\n");
    }
    else if (keycode == KEY_S)
    {
        player->pypos_x = player->pypos_x - (player->dir_x * player->move_speed);
        player->pypos_y = player->pypos_y - (player->dir_y * player->move_speed);
        printf("Moving Backward\n");
    }
    else if (keycode == KEY_D)
    {
        player->pypos_x = player->pypos_x + (player->camera_x * player->move_speed);
        player->pypos_y = player->pypos_y + (player->camera_y * player->move_speed);
        printf("Moving Right\n");
    }
    else if (keycode == KEY_RIGHT)
    {
        player->dir_x = (olddir_x * cos(player->rotation_speed) - (olddir_y * sin(player->rotation_speed)));
        player->dir_y = (olddir_x * sin(player->rotation_speed) + (olddir_y * cos(player->rotation_speed)));
        player->dir_x = (olddir_x * cos(player->camera_x) - (olddir_y * sin(player->camera_y)));
        player->dir_y = (olddir_x * sin(player->camera_x) + (olddir_y * cos(player->camera_y)));
    }
    else if (keycode == KEY_LEFT)
    {
        player->dir_x = (olddir_x * cos(player->rotation_speed) + (olddir_y * sin(player->rotation_speed)));
        player->dir_y = (olddir_x * sin(player->rotation_speed) - (olddir_y * cos(player->rotation_speed)));
        player->dir_x = (olddir_x * cos(player->camera_x) - (olddir_y * sin(player->camera_y)));
        player->dir_y = (olddir_x * sin(player->camera_x) + (olddir_y * cos(player->camera_y)));
    }
    else if (keycode == KEY_ESC)
    {
        printf("Close\n");
        exit(0);
    }
    return 0;
}

int close_game(t_player *player)
{
    (void)player;
    printf("Game closed\n");
    exit(0);
    return (0);
}

#include "include/map.h"
int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_player 	player = {0};
	t_data      img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "cub3D");

	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    draw_map(&img);
    draw_player(&img, &player);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	(void)mlx_win;
	mlx_key_hook(mlx_win, handle_key, &player);
	mlx_hook(mlx_win, 17, 0, close_game, &player);
	mlx_loop(mlx);
	return 0;
}
