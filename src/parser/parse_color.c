#include "cub3D.h"

static int	is_digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i] || str[i] == '\n')
		return (0);
	while (str[i] && str[i] != '\n' && str[i] != '\r' && str[i] != ' ')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	get_color(char *line)
{
	char		**temp;
	int			len;
	signed int	r;
	signed int	g;
	signed int	b;

	len = 0;
	temp = ft_split(line + 2, ',');
	while (temp[len])
		len++;
	if (len != 3 || !is_digits_only(temp[0]) 
		|| !is_digits_only(temp[1]) || !is_digits_only(temp[2]))
	{
		free_split(temp);
		return (-1);
	}
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	free_split(temp);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
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
