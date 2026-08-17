
#include "include/map.h"
#include <fcntl.h>

t_map	*parse(int fd)
{
	t_map	*map;

	
}

t_map	*parse_cub_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	return (parse(fd));
}
