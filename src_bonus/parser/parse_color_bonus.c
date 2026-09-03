/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:04:43 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:04:44 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_component(char *component)
{
	int	value;

	while (*component == ' ' || *component == '\t')
		component++;
	if (*component < '0' || *component > '9')
		return (-1);
	value = 0;
	while (*component >= '0' && *component <= '9')
	{
		value = value * 10 + (*component - '0');
		if (value > 255)
			return (-1);
		component++;
	}
	while (*component == ' ' || *component == '\t'
		|| *component == '\r' || *component == '\n')
		component++;
	if (*component != '\0')
		return (-1);
	return (value);
}

static int	get_color(char *line)
{
	char		**temp;
	int			len;
	signed int	red;
	signed int	green;
	signed int	blue;

	while (*line == ' ' || *line == '\t')
		line++;
	len = 0;
	temp = ft_split(line + 1, ',');
	while (temp[len])
		len++;
	if (len != 3)
	{
		free_split(temp);
		return (-1);
	}
	red = parse_component(temp[0]);
	green = parse_component(temp[1]);
	blue = parse_component(temp[2]);
	free_split(temp);
	if ((red < 0 || red > 255) || (green < 0 || green > 255)
		|| (blue < 0 || blue > 255))
		return (-1);
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
