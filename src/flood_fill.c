#include "cub3D.h"
#include "include/map.h"

int	flood(t_map *map, int x, int y)
{
	if ((size_t)y >= map->size.height || (size_t)x >= ft_strlen(map->grid[y]))
		return (0);
	if (is_spawn_point(map->grid[y][x])
		&& ((size_t)x != map->spawn.x || (size_t)y != map->spawn.y))
		return (0);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'V')
		return (1);
	if (map->grid[y][x] == ' ')
		return (0);
	if (map->grid[y][x] != '0' && !is_spawn_point(map->grid[y][x]))
		return (0);
	map->grid[y][x] = 'V';
	return (flood(map, x + 1, y) && flood(map, x - 1, y)
		&& flood(map, x, y + 1) && flood(map, x, y - 1));
}
