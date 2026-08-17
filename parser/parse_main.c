
#include "include/map.h"

int	main(void)
{
	t_map	*map = {0};

	map = parse_cub_file("maps/map3.cub");
	if (!map)
	{
		printf("Error\n");
		return (1);
	}
	printf("==================Map Data==================\n");
	printf("height: %d\n", map->height);
	printf("width: %d\n", map->width);
	printf("c_color: %d\n", map->celing_color);
	printf("f_color: %d\n", map->floor_color);
	printf("==================  MAP   ==================\n");
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			printf("%s ", map->map[i][j]);
		}
		printf("\n");
	}
}
