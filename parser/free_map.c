
#include "include/map.h"

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->path_e)
			free(map->path_e);
		if (map->path_n)
			free(map->path_n);
		if (map->path_s)
			free(map->path_s);
		if (map->path_w)
			free(map->path_w);
		if (map->map != NULL)
		{
			i = 0;
			while (i < (int)map->height && map->map[i])
			{
				free(map->map[i]);
				i++;
			}
			free(map->map);
		}
		free(map);
	}
}
