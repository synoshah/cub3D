#include "../include/map.h"
#include "../libft/libft.h"

int	is_texture_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;	
	return (!ft_strncmp(line + i, "NO", 2)
		|| !ft_strncmp(line + i, "SO", 2)
		|| !ft_strncmp(line + i, "WE", 2)
		|| !ft_strncmp(line + i, "EA", 2));
}

int	is_color_line(char *line)
{
	if (!line)
		return (1);
	return (line[0] == 'F'
		|| line[0] == 'C');
}

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'
			|| line[i] == '\r' || line[i] == '\n'))
		i++;
	return (line[i] == '\0');
}

int	all_textures_found(int *found_textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!found_textures[i])
			return (0);
		i++;
	}
	return (1);
}

int	add_texture(int *found_textures, char *line)
{
	static char	*ids[4] = {"NO", "SO", "WE", "EA"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(line, ids[i], 2))
		{
			if (found_textures[i])
				return (0);
			found_textures[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
