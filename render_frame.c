#include "cub3D.h"
#include "include/map.h"
#include "include/draw.h"

// don't need handle_key here, main.c is already listening for key presses in the background

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
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;

    clear_display(img);
    draw_map(img);
    draw_player(img, player);

    // Ze Loop
    while (x < 800)
    {
        int hit = 0;
        int mapX = (int)player->pypos_x;
        int mapY = (int)player->pypos_y;
        //find the exact direction of this specific ray
        multiplier = (2.0 * x / 800.0) - 1.0;
        ray_dir_x = player->dir_x + (player->camera_x * multiplier);
        ray_dir_y = player->dir_y + (player->camera_y * multiplier);
        // we can calculate the strides
        deltaDistX = fabs(1.0 / ray_dir_x);
        deltaDistY = fabs(1.0 / ray_dir_y);
        //calculate the mini steps x axis
        if (ray_dir_x < 0)
        {
            stepX = -1;
            sideDistX = (player->pypos_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->pypos_x) * deltaDistX;
        }
        if (ray_dir_y < 0)
        {
            stepY = -1;
            sideDistY = (player->pypos_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->pypos_y) * deltaDistY;
        }
        int start_x = player->pypos_x * TILE_SIZE;
        int start_y = player->pypos_y * TILE_SIZE;
        int end_x = start_x + (ray_dir_x * 50);
        int end_y = start_y + (ray_dir_y * 50);
        draw_line(img, start_x, start_y, end_x, end_y, 0x00FF00); 

        x++;
    }
    mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, img->img, 0, 0);
    return (0);
}

