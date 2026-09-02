#include "../include/parser.h"

static int	get_color(char *line)
{
	char		**temp;
	int			len;
	signed int	red;
	signed int	green;
	signed int	blue;

	len = 0;
	temp = ft_split(line + 2, ',');
	while (temp[len])
		len++;
	if (len != 3)
	{
		free_split(temp);
		return (-1);
	}
	red = ft_atoi(temp[0]);
	green = ft_atoi(temp[1]);
	blue = ft_atoi(temp[2]);
	free_split(temp);
	return ((red << 16) | (green << 8) | blue);
}

int	add_color(t_colors *colors, char *line, t_flags *flags)
{
	int	i;
	int	color;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	color = get_color(line);
	if (line[i] == 'F' && !(flags->found_floor) && color != -1)
	{
		flags->found_floor = 1;
		colors->floor = color;
	}
	else if (line[i] == 'C' && !(flags->found_ceiling) && color != -1)
	{
		flags->found_ceiling = 1;
		colors->ceiling = color;
	}
	else
		return (0);
	return (1);
}
