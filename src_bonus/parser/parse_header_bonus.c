/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:04:17 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:04:17 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// looks for the texture and color
// identifiers in the file
// sets it as found in t_flags
// and puts its value inside t_map
// Returns 1 for valid headers and blank lines.
// Returns 0 for valid map rows.
// Returns -1 for invalid or misplaced headers
static int	apply_header_entry(t_map *map, t_flags *flags, char *line)
{
	if (flags->in_map)
	{
		if (is_blank_line(line) || is_texture_line(line)
			|| is_color_line(line))
			return (-1);
	}
	if (is_blank_line(line))
		return (1);
	if (is_texture_line(line))
	{
		if (!add_texture(&map->textures, flags, line))
			return (-1);
		return (1);
	}
	if (is_color_line(line))
	{
		if (!add_color(&map->colors, line, flags))
			return (-1);
		return (1);
	}
	flags->in_map = 1;
	return (0);
}

// gets height and width of map.
static int	update_map_dimensions(char *line, t_flags *flags)
{
	int	len;

	if (line && !is_blank_line(line)
		&& !is_texture_line(line) && !is_color_line(line))
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			line[--len] = '\0';
		if (len > flags->width)
			flags->width = len;
		flags->height++;
		return (1);
	}
	return (0);
}

// calls both the
// apply_header_entry and update_map_dimensions() functions.
// checks if the map has all the necessary information
// and puts them into the t_flags as well as t_map structs.
static int	scan_cub_file(t_map *map, t_flags *flags, int fd)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		result = apply_header_entry(map, flags, line);
		if (result == 0 && !update_map_dimensions(line, flags))
			result = -1;
		if (result < 0)
		{
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

// checks the values inside t_flags
int	parse_map_metadata(t_map *map, int fd)
{
	t_flags	flags;

	ft_memset(&flags, 0, sizeof(flags));
	if (!scan_cub_file(map, &flags, fd))
		return (0);
	map->size.height = flags.height;
	map->size.width = flags.width;
	if (!all_textures_found(flags.found_textures)
		|| !flags.found_floor || !flags.found_ceiling)
	{
		printf("Error\nFailed to find all textures and colors\n");
		return (0);
	}
	return (1);
}
