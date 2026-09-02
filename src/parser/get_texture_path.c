#include "../include/parser.h"

static int	validate_and_add_path(char *line, char **destinations)
{
	char	*path;
	int		fd;

	path = ft_strtrim(line, "\n\t \r");
	if (!path || !path[0])
		return (0);
	fd = open(path, 0);
	if (fd < 0)
	{
		printf("File %s doesnt exits\n", path);
		free(path);
		return (0);
	}
	close(fd);
	*destinations = path;
	return (1);
}

int	add_texture(t_textures *tex, t_flags *flags, char *line)
{
	static char	*ids[4] = {"NO", "SO", "WE", "EA"};
	char		**destinations[4];
	int			i;

	destinations[0] = &tex->north;
	destinations[1] = &tex->south;
	destinations[2] = &tex->west;
	destinations[3] = &tex->east;
	while (*line == ' ' || *line == '\t')
		line++;
	i = -1;
	while (i++ < 4)
	{
		if (!ft_strncmp(line, ids[i], 2))
		{
			if (flags->found_textures[i])
				return (0);
			if (!validate_and_add_path(line + 2, destinations[i]))
				return (0);
			flags->found_textures[i] = 1;
			return (1);
		}
	}
	return (0);
}
