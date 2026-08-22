
#include "../include/map.h"
#include <stdio.h>

t_map	*parse_cub_file(char *filename);

// TODO: Use the new structs inside map.h
int	main(void)
{
	t_map	*map;
    // t_player 	player = {0};

	// player.pypos_x = 5.0; 
	// player.pypos_y = 5.0;
	// player.dir_x = 0.0;
	// player.dir_y = -1.0;
	// player.camera_x = 0.66;
	// player.camera_y = 0.0;
	// player.move_speed = 0.2;
	// player.rotation_speed = 0.05;

	map = parse_cub_file("maps/map3.cub");
	if (!map)
	{
		printf("Error\n");
		return (1);
	}
	printf("==================Map Data==================\n");
	printf("height: %ld\n", map->size.height);
	printf("width: %ld\n", map->size.width);
	printf("c_color: %d\n", map->colors.ceiling);
	printf("f_color: %d\n", map->colors.floor);
	printf("==================  MAP   ==================\n");
	for (int i = 0; i < (int)map->size.height; i++)
	{
		for (int j = 0; j < (int)map->size.width; j++)
		{
			if (map && map->grid && map->grid[i])
				printf("%d ", map->grid[i][j]);
		}
		printf("\n");
	}
	free_map(map);
}
