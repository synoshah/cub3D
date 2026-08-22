#include "cub3D.h"
#include "include/map.h"
#include "include/draw.h"

extern int MAP[24][24];

int render_frame(t_context *ctx)
{
    t_player *player = ctx->player;
    t_data *img = ctx->img;
    handle_key(ctx);
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
    int side;

    clear_display(img);
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
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX = deltaDistX + sideDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY = deltaDistY + sideDistY;
                mapY += stepY;
                side = 1;
            }
            if (MAP[mapY][mapX] > 0)
                hit = 1;
        }
        //calculate the real distance to the wall
        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        // calculate the height of the 3d wall slice
        int lineHeight = (int)(600 / perpWallDist);
        // find exactly where to draw the wall on the screen
        int drawStart = -lineHeight / 2 + 600 / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + 600 / 2;
        if (drawEnd >= 600)
            drawEnd = 600 - 1; //do not draw past the bottom of the window
        // give the walls temp colors for fake lighting
        int color = 0x0000FF; // Blue wall
        if (side == 1)
            color = 0x000088; // darker blue if it's a north or south wall
        // draw the vertical 3d slice 
        draw_line(img, x, drawStart, x, drawEnd, color);
        x++;
    }
    mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, img->img, 0, 0);
    return (0);
}
