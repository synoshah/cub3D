#include "cub3D.h"
#include "include/map.h"
#include "include/draw.h"

// Comments for context

int render_frame(t_context *ctx)
{
    t_player *player = ctx->player;
    t_data *img = ctx->img;
    
    // pulll keyboard input and update player coordinates before drawing to prevent input lag
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

    // Paint (top half ceiling color, bottom half floor color)
    draw_background(img, ctx->map->colors.ceiling, ctx->map->colors.floor);

    // Fire exactly 800 rays (one for every vertical pixel column on the monitor)
    while (x < 800)
    {
        int hit = 0;
        
        // cast the decimal position into an integer to find the starting 2D grid block (5.2 == 5)
        int mapX = (int)player->pypos_x;
        int mapY = (int)player->pypos_y;
        
        // scale the current pixel (x) to the camera plane (-1.0 to 1.0)
        multiplier = (2.0 * x / 800.0) - 1.0;
        
        // calculate the ray's vector by adding a fraction of the camera plane to the direction vector
        ray_dir_x = player->dir_x + (player->camera_x * multiplier);
        ray_dir_y = player->dir_y + (player->camera_y * multiplier);
        
        //ccalculate the constant diagonal strides needed to cross 1 full grid block
        // fabs to remove negative signs because distance magnitude cannot be negative.
        deltaDistX = fabs(1.0 / ray_dir_x);
        deltaDistY = fabs(1.0 / ray_dir_y);
        
        // determine the direction to step and the distance to the very first grid intersection
        if (ray_dir_x < 0) // moving left
        {
            stepX = -1;
            sideDistX = (player->pypos_x - mapX) * deltaDistX;
        }
        else // moving right
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->pypos_x) * deltaDistX;
        }
        
        if (ray_dir_y < 0) // moving up
        {
            stepY = -1;
            sideDistY = (player->pypos_y - mapY) * deltaDistY;
        }
        else // moving down
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->pypos_y) * deltaDistY;
        }
        
        // jump from intersection to intersection until a wall is found
        while (hit == 0)
        {
            // If the x axis intersection is closer, jump there
            if (sideDistX < sideDistY)
            {
                sideDistX = deltaDistX + sideDistX; // prep stopwatch for the next x jump
                mapX += stepX;                      // move array tracker horizontally
                side = 0;                           // record an east/west wall hit
            }
            // if the y axis intersection is closer, jump there
            else
            {
                sideDistY = deltaDistY + sideDistY; // prep stopwatch for the next y jump
                mapY += stepY;                      // move array tracker vertically
                side = 1;                           // record a north/south wall hit
            }
            
            // check to see the ray has not flown outside the parsed map boundaries
            if (mapX < 0 || mapY < 0 || 
                (size_t)mapY >= ctx->map->size.height || 
                (size_t)mapX >= ft_strlen(ctx->map->grid[mapY]))
                hit = 1; 
                
            // check the valid map coordinate for a wall
            else if (ctx->map->grid[mapY][mapX] == '1')
                hit = 1;
        }
        
        // the stopwatch already ticked forward for the next jump. Subtract one stride to rewind to the wall face.
        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
            
        // stop crashes if the player clips slightly inside a wall
        if (perpWallDist <= 0.0001)
            perpWallDist = 0.0001;

        // Wall height is inversely proportional to distance (closer = bigger, further = smaller)
        int lineHeight = (int)(600 / perpWallDist);
        
        // center the 3d wall mathematically on the 600 pixel y axis horizon
        int drawStart = -lineHeight / 2 + 600 / 2;
        if (drawStart < 0)
            drawStart = 0; // clamp to the ceiling to prevent writing to unallocated memory
            
        int drawEnd = lineHeight / 2 + 600 / 2;
        if (drawEnd >= 600)
            drawEnd = 600 - 1; // clamp to the floor
            
        // find the exact decimal percentage of where the ray struck the wall block (e.g., 0.25)
        double wallX;
        if (side == 0)
            wallX = player->pypos_y + perpWallDist * ray_dir_y;
        else 
            wallX = player->pypos_x + perpWallDist * ray_dir_x;
        wallX -= floor(wallX); // strip the integer, keep only the decimal fraction
        
        // map that decimal percentage to the exact X-column of a 64x64 pixel image
        int texX = (int)(wallX * 64.0);
        
        // flip the texture rendering mathematically so the image doesn't look mirrored from the back
        if (side == 0 && ray_dir_x > 0)
            texX = 64 - texX - 1;
        if (side == 1 && ray_dir_y < 0) 
            texX = 64 - texX - 1;

        // calculate the scaling ratio. how many texture pixels to advance per monitor pixel
        double step = 1.0 * 64.0 / lineHeight;
        
        // determine the exact texture starting coordinate based on how much of the wall is clamped off screen
        double texPos = (drawStart - 600 / 2 + lineHeight / 2) * step;

        // Fake lighting
        int color = 0x0000FF; 
        if (side == 1)
            color = 0x000088; 
            
        int y = drawStart;
        while (y < drawEnd)
        {
            // mask the coordinate with bitwise and to ensure it safely wraps between 0 and 63
            int texY = (int)texPos & (64 - 1);
            (void)texY;
            texPos += step; // advance down the image file
            // my_pixel_put(img, x, y, color); // i think it will go here in the future
            y++;
        }
        // temporary solid color drawing
        draw_line(img, x, drawStart, x, drawEnd, color);
        
        // advance to the next ray column on the monitor
        x++;
    }
    mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, img->img, 0, 0);
    return (0);
}
