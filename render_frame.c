#include "cub3D.h"
#include "include/map.h"
#include "include/draw.h"

int render_frame(t_context *ctx)
{
    t_player *player = ctx->player;
    t_data *img = ctx->img;
    int x = 0;
    double multiplier;
    double ray_dir_x;
    double ray_dir_y;
    int stepX;
    int stepY;
    int side;
    double deltaDistX;
    double deltaDistY;

    clear_display(img);
    // draw the map
    draw_map(img);
    draw_player(img, player);
    // draw 800 rays
    while (x < 800)
    {
        int hit = 0;
        int mapX = (int)player->pypos_x;
        int mapY = (int)player->pypos_y;
        multiplier = (2.0 * x / 800.0) - 1.0;
        ray_dir_x = player->dir_x + (player->camera_x * multiplier);
        ray_dir_y = player->dir_y + (player->camera_y * multiplier);
        // calculate line coordinates for the 2d map
        int start_x = player->pypos_x * TILE_SIZE;
        int start_y = player->pypos_y * TILE_SIZE;
        // multiply ray_dir by 50 just to make the line long enough to see
        int end_x = start_x + (ray_dir_x * 50);
        int end_y = start_y + (ray_dir_y * 50);
        draw_line(img, start_x, start_y, end_x, end_y, 0x00FF00); // green lasers
        x++;
    }
    // push the final completed image to the window
    mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, img->img, 0, 0);
    return (0);
}
