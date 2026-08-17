
#include "../include/map.h"
#include <stdio.h>

t_map	*parse_cub_file(char *filename);

int	main(void)
{
	t_map	*map;

	map = parse_cub_file("maps/map3.cub");
	if (!map)
	{
		printf("Error\n");
		return (1);
	}
	printf("==================Map Data==================\n");
	printf("height: %ld\n", map->height);
	printf("width: %ld\n", map->width);
	printf("c_color: %d\n", map->celing_color);
	printf("f_color: %d\n", map->floor_color);
	printf("==================  MAP   ==================\n");
	for (int i = 0; i < (int)map->height; i++)
	{
		for (int j = 0; j < (int)map->width; j++)
		{
			if (map && map->map && map->map[i])
				printf("%d ", map->map[i][j]);
		}
		printf("\n");
	}
	free_map(map);
}
