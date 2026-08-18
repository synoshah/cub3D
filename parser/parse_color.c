
#include "include/map.h"
#include "../libft/libft.h"

int	get_color(char *line)
{
	char		**temp;
	signed int	red;
	signed int	green;
	signed int	blue;

	temp = ft_split(line + 2, ',');
	red = ft_atoi(temp[0]);
	green = ft_atoi(temp[1]);
	blue = ft_atoi(temp[2]);

	// TODO:
	free_split(temp);
	return ((red << 16) | (green << 8) | blue);
}
