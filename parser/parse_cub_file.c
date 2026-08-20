
#include "../include/map.h"
#include <fcntl.h>
#include "../libft/libft.h"
int	flood(t_map *map, size_t x, size_t y);

int	parse_header_and_map(t_map *map, int fd)
{
	char	*line;

	// states:
	int	*found_textures;
	int	in_map;
	int	found_floor;
	int	found_ceiling;
	int	height;
	int	width;

	// temp
	int	len;
	
	found_textures = ft_calloc(4, sizeof(int));
	in_map = 0;
	found_ceiling = 0;
	found_floor = 0;
	width = 0;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_blank_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!in_map && is_texture_line(line))
		{
			if (!add_texture(&map->textures, found_textures, line))
			{
				printf("failed to add texture\n");
				free(line);
				free(found_textures);
				return (0);
			}
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!in_map && is_color_line(line))
		{
			// TODO: add_color(map->colors, line);
			// printf("failed to add color\n");
			if (line[0] == 'F')
			{
				found_floor = 1;
				map->colors.floor = get_color(line);
			}
			else if (line[0] == 'C')
			{
				found_ceiling = 1;
				map->colors.ceiling = get_color(line);
			}
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		in_map = 1;
		while (line && !is_blank_line(line))
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[--len] = '\0';
			if (len > width)
				width = len;
			height++;
			free(line);
			line = get_next_line(fd);
		}
	}
	if (line)
		free(line);
	// final_check
	if (!all_textures_found(found_textures) || !found_floor || !found_ceiling)
	{
		printf("failed to find all textures and colors\n");
		free(found_textures);
		return (0);
	}
	free(found_textures);
	map->size.height = height;
	map->size.width = width;
	return (1);
}

int	fill_map(t_map *map, int fd)
{
	char	*line;
	int		i;
	int		in_map;
	int		len;

	map->grid = ft_calloc(map->size.height, sizeof(char *));
	if (!map->grid)
		return (0);
	i = 0;
	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!in_map && is_blank_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_texture_line(line) || is_color_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		len = ft_strlen(line);

		if (len > 0 && line[len - 1] == '\n')
			line[--len] = '\0';
		// Look for spawn point here maybe?
		// y will be i and x will be the index inside len using strchr()?
		int	x = 0;
		int	found = 0;
		while (!found && line[x])
		{
			if (is_spawn_point(line[x]))
			{
				map->spawn.y = i;
				map->spawn.x = x;
				map->spawn.direction = line[x];
				found = 1;
			}
			x++;
		}
		map->grid[i] = ft_strdup(line);
		if (!map->grid[i])
		{
			printf("failed to copy map\n");
			return (0);
		}
		in_map = 1;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (1);
}

t_map	*parse_cub_file(char *filename)
{
	t_map	*map;
	int	fd;

	map = ft_calloc(1, sizeof(*map));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (NULL);
	}
	if (!parse_header_and_map(map, fd))
	{
		close (fd);
		free_map(map);
		return (NULL);
	}
	close(fd);
	fd = open (filename, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		return (NULL);
	}
	if (!fill_map(map, fd))
	{
		close(fd);
		free_map(map);
		return (NULL);
	}
	close(fd);
	if (!flood(map, (int)map->spawn.x, (int)map->spawn.y))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
