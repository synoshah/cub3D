
#include "include/draw.h"
#include "include/shapes.h"
#include "../cub3D.h"

#define HEIGHT 24
#define WIDTH 24

// It's temporarily a global variable.
int MAP[WIDTH][HEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	clear_display(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < 800)
	{
		j = 0;
		while (j < 600)
		{
			my_pixel_put(img, i, j, 0);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *img)
{
	int	i;
	int	j;
	// int	i_offset;
	// int	j_offset;

	i = 0;
	// i_offset = 0;
	// j_offset = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (MAP[i][j] > 0)
			{
				if (MAP[i][j] == 2)
					draw_square(img, j *TILE_SIZE, i*TILE_SIZE, 0xFF0025, TILE_SIZE);
				else if (MAP[i][j] == 3)
					draw_square(img, j *TILE_SIZE, i*TILE_SIZE, 0xFF0025, TILE_SIZE);
				else if (MAP[i][j] == 4)
					draw_square(img, j *TILE_SIZE, i*TILE_SIZE, 0x0FF025, TILE_SIZE);
				else if (MAP[i][j] == 5)
					draw_square(img, j *TILE_SIZE, i*TILE_SIZE, 0xFF0F02, TILE_SIZE);
				else
					draw_square(img, j *TILE_SIZE, i*TILE_SIZE, 0xFFFFFFFF, TILE_SIZE);
			}
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *img, t_player *player)
{
	int	x_pos;
	int	y_pos;

	if (player->pypos_x > 0)
		x_pos = player->pypos_x * TILE_SIZE;
	if (player->pypos_y > 0)
		y_pos = player->pypos_y * TILE_SIZE;
	draw_circle(img, x_pos, y_pos, 0xFF0000FF, 4);
}
