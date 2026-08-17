
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
			get_color(map, line);
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
	(void)map;
	(void)fd;
	return (1);
}

t_map	*parse(int fd)
{
	t_map	*map;

	map = malloc (sizeof(t_map *));
	if (!map)
		return (NULL);
	if (!get_elements(map, fd))
	{
		free_map(map);
		return (NULL);
	}
	map->map = NULL;
	if (!get_map(map, fd))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}

t_map	*parse_cub_file(char *filename)
{
	t_map	*map;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (NULL);
	}
	map = parse(fd);
	close(fd);
	return (map);
}
