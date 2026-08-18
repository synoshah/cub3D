
#include "../include/map.h"
#include <fcntl.h>
#include "../libft/libft.h"

int	get_elements(t_map *map, int fd)
{
	char	*line;
	int		i;
	int		element_count;

	// count the elements found so far. total of 6
	element_count = 0;

	line = get_next_line(fd);
	while (line && element_count < 6)
	{
		i = 0;
		while (line[i] == ' ') // skip trailing space
			i++;
		// check if texture path
		if (!ft_strncmp(&line[i], "NO", 2) ||
			!ft_strncmp(&line[i], "SO", 2) ||
			!ft_strncmp(&line[i], "WE", 2) ||
			!ft_strncmp(&line[i], "EA", 2))
		{
			printf("%s\n", &line[i+3]);
			get_tex(map, line);
			element_count++;
		}
		// else check if color
		else if (line[i] == 'F' ||
					line[i] == 'C')
		{
			printf("%s\n", &line[i+2]);
			get_color(line);
			element_count++;
		}
		// if we're doing neither then we found them all or some are missing.
		else if (ft_isdigit(line[i]) && element_count <= 6)
		{
			free(line);
			return (0);
		}	
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}

int	get_map(t_map *map, int fd)
{
	char	*line;
	int		i;

	map->map = ft_calloc(/*map->height*/5, sizeof(char *));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		// map is char **
		map->map[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}

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
			if (!add_texture(found_textures, line))
			{
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
			if (line[0] == 'F')
			{
				found_floor = 1;
				map->floor_color = get_color(line);
			}
			else if (line[0] == 'C')
			{
				found_ceiling = 1;
				map->celing_color = get_color(line);
			}
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		in_map = 1;
		while (line && !is_blank_line(line))
		{
			len = ft_strlen(line);
			
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
		free(found_textures);
		return (0);
	}
	free(found_textures);
	map->height = height;
	map->width = width;
	return (1);
}

int	fill_map(t_map *map, int fd)
{
	char	*line;
	int		i;
	int		in_map;

	map->map = ft_calloc(map->height, sizeof(char *));
	if (!map->map)
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

		// TODO:
		// fill map
		map->map[i] = ft_strdup(line);
		if (!map->map[i])
			return (0);
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
	return (map);
}
