#include "cub3D.h"
#include "include/map.h"
#include "include/draw.h"
#include "include/game_state.h"
#include "include/parser.h"

// Comments for context
void load_texture(void *mlx, t_data texture[], char *file_path);

int render_frame(t_context *ctx)
{
	t_player *player = ctx->player;
	t_data *img = ctx->img;
	t_game_state    *game_state = ctx->game_state;
	
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

	if (game_state->gamemode == START)
	{
		t_data	temp_img = {0};
		load_texture(ctx->mlx, &temp_img, "textures/hii.xpm");
		mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, temp_img.img, 0, 0);
		mlx_string_put(ctx->mlx, ctx->mlx_win, 250, 300, 0x111111, "press w to start playing!");
	}
	// Paint (top half ceiling color, bottom half floor color)
	else if (game_state->gamemode == PLAYING)
	{
		mlx_clear_window(ctx->mlx, ctx->mlx_win);

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
					(size_t)mapX >= ctx->map->size.width)
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
			
			// Find texture index (0 to 3) based on wall hit
			int texture_index = 0;
			
			if (side == 0)
			{
				if (ray_dir_x > 0)
					texture_index = 2; // East
				else
					texture_index = 3; // West
			}
			else
			{
				if(ray_dir_y > 0)
					texture_index = 1;
				else
					texture_index = 0;
			}
			t_data *texture = &ctx->textures[texture_index];

			// map that decimal percentage to the exact X-column of the actual texture image
			int texX = (int)(wallX * (double)texture->width);
			
			// flip the texture rendering mathematically so the image doesn't look mirrored from the back
			if (side == 0 && ray_dir_x > 0)
				texX = texture->width - texX - 1;
			if (side == 1 && ray_dir_y < 0) 
				texX = texture->width - texX - 1;
			if (texX < 0)
				texX = 0;
			if (texX >= texture->width)
				texX = texture->width - 1;
	
			// calculate the scaling ratio. how many texture pixels to advance per monitor pixel
			double step = 1.0 * texture->height / lineHeight;
			
			// determine the exact texture starting coordinate based on how much of the wall is clamped off screen
			double texPos = (drawStart - 600 / 2 + lineHeight / 2) * step;

			int y = drawStart;
			while (y < drawEnd)
			{
				int texY = (int)texPos;
				if (texY < 0)
					texY = 0;
				if (texY >= texture->height)
					texY = texture->height - 1;
				texPos += step;
	
				// get pixel color from our image memory
				int color = get_texture_pixel(texture, texX, texY);

				// fake Lighting
				//shifts all the binary bits one slot to the right,
				// which divides the whole number by 2 instantly.
				if (side == 1)
					color = (color >> 1) & 0x7F7F7F; // darken the color by 50%
				
				// paint it to the screen
				my_pixel_put(img, x, y, color);
				y++;
			}
			// advance to the next ray column on the monitor
			x++;
		}
		mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, img->img, 0, 0);
	}
	else
	{
		if (game_state->gamemode == WON)
		{
			game_state->level++;
			if (game_state->level > 1)
			{
				game_state->gamemode = DONE;
				return(1) ;
			}
			// load_next_map();
			free_map(ctx->map);
			 ctx->map = parse_map_file("maps/map3.cub");
			if (!ctx->map)
			{
				printf("failed to parse map:\n\n\\n\n");
				exit(1);
			}

			ctx->player->pypos_x = ctx->map->spawn.x + 0.1;
			ctx->player->pypos_y = ctx->map->spawn.y + 0.1;

			// reset direction based on map->spawn.direction
			if (ctx->map->spawn.direction == 'N')
			{
				ctx->player->dir_x = 0.0;
				ctx->player->dir_y = -1.0;
				ctx->player->camera_x = 0.66;
				ctx->player->camera_y = 0.0;
			}
			game_state->gamemode = PLAYING;
		}
		else
		{
			t_data	temp_img = {0};
			load_texture(ctx->mlx, &temp_img, "textures/end_screen.xpm");
			mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, temp_img.img, 0, 0);
		}
	}
	return (0);
}
