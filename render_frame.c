#include "cub3D.h"

int render_frame(t_player *player)
{
    int x = 0;
    double camera_x; // Tracking (-1.0 to 1.0)
    double ray_dir_x; // The x vector of ray
    double ray_dir_y; // The y vector of ray
    while (x < 800)
    {
        // Find pixel position between -1 and 1;
        camera_x = (2.0 * x / (double)800) - 1.0;
        // shoot ray from that point
        ray_dir_x = player->dir_x + (player->camera_x * camera_x);
        ray_dir_y = player->dir_y + (player->camera_y * camera_x);
        if (x == 400)
            printf("Center %f, %f\n", ray_dir_x, ray_dir_y);
        x++;
    }
    return 0;
    // center = (2 * num of pixels / total screen width) - 1
}
