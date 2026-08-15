#include "cub3D.h"

int handle_key(int keycode, t_player *player)
{
    if (keycode == KEY_W)
    {
        player->pypos_y = player->pypos_y + (player->dir_y * player->move_speed);
        //Formula: New Position = Current Position + (Direction * Speed)
        //pos_x = pos_x + (dir_x * 0.2)
        //pos_y = pos_y + (dir_y * 0.2)
        printf("Moving Forward\n");
    }
    else if (keycode == KEY_A)
        printf("Moving Left\n");
    else if (keycode == KEY_S)
        printf("Moving Backward\n");
    else if (keycode == KEY_D)
        printf("Moving Right\n");
    else if (keycode == KEY_ESC)
    {
        printf("Close\n");
        exit(0);
    }
    return 0;
}

int close_game(t_player *player)
{
    printf("Game closed\n");
    exit(0);
    return (0);
}

int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_player player;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 800, 600, "cub3D");
    (void)mlx_win;
    mlx_key_hook(mlx_win, handle_key, &player);
    mlx_hook(mlx_win, 17, 0, close_game, &player);
    mlx_loop(mlx);
    return 0;
}