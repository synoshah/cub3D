/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:02:03 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:02:03 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	open_and_read_header(t_map *map, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (0);
	}
	if (!parse_map_metadata(map, fd))
	{
		close (fd);
		free_map(map);
		return (0);
	}
	close(fd);
	return (1);
}

static int	open_and_load_map(t_map *map, char *filename)
{
	int	fd;

	fd = open (filename, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		return (0);
	}
	if (!load_map_grid(map, fd))
	{
		free_map(map);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

t_map	*parse_map_file(char *filename)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	if (!open_and_read_header(map, filename))
		return (NULL);
	if (!open_and_load_map(map, filename))
		return (NULL);
	if (!flood(map, (int)map->spawn.x, (int)map->spawn.y))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
