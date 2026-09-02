#include "../include/parser.h"

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->textures.east)
			free(map->textures.east);
		if (map->textures.north)
			free(map->textures.north);
		if (map->textures.south)
			free(map->textures.south);
		if (map->textures.west)
			free(map->textures.west);
		if (map->grid != NULL)
		{
			i = 0;
			while (i < (int)map->size.height && map->grid[i])
			{
				free(map->grid[i]);
				i++;
			}
			free(map->grid);
		}
		free(map);
	}
	map = NULL;
}
